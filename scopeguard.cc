// g++ -o t -std=c++11 scopeguard.cc
#include <stdio.h>
#include <iostream>
#include <functional> // for function
#include <memory>     // for unique_ptr

class ScopeGuard
{
public:
    explicit ScopeGuard(std::function<void()> onExitScope)
        : onExitScope_(onExitScope), dismissed_(false)
    { }

    ~ScopeGuard()
    {
        if (!dismissed_)
        {
            onExitScope_();
        }
    }

    void Dismiss()
    {
        dismissed_ = true;
    }

private:
    std::function<void()> onExitScope_;
    bool dismissed_;

private: // non-copyable
    ScopeGuard(ScopeGuard const&);
    ScopeGuard& operator=(ScopeGuard const&);
};

#define SCOPEGUARD_LINENAME_CAT(name, line) name##line
#define SCOPEGUARD_LINENAME(name, line) SCOPEGUARD_LINENAME_CAT(name, line)

#define ON_SCOPE_EXIT(callback) ScopeGuard SCOPEGUARD_LINENAME(EXIT, __LINE__)(callback)

class A
{
public:
    A () { std::cout << "Enter A()\n"; }
    ~A () { std::cout << "Enter ~A()\n"; }
};

A* create_instance() { return new A(); }
void release_instance(A* a) {
    delete a;
    std::cout << "do release A" << std::endl;
}

class C
{
public:
    C () { std::cout << "Enter C()\n"; }
    ~C () { std::cout << "Enter C()\n"; }
    void Fun1() {
        A* a = create_instance();
        // We are not need to care about the variable name when use this macro
        ON_SCOPE_EXIT( [&] { release_instance(a);} );

        A* b = create_instance();
        ON_SCOPE_EXIT( [&] { release_instance(b);} );
        // expect release a and b when outside
    }
    void Fun2() {
        A* a = create_instance();
        ScopeGuard aSG( [&] { release_instance(a);} );
        std::cout << "do something in Fun1" << std::endl;
        std::cout << "throw exception" << std::endl;
        // expect release a when outside
    }
    void Fun3() {
        A* a = create_instance();
        ScopeGuard aSG( [&] { release_instance(a);} );
        std::cout << "do something in Fun1" << std::endl;
        std::cout << "throw exception" << std::endl;
        // Remember to call this if you don't want to release resource
        aSG.Dismiss(); // expect not release a
    }
    void Fun4() {
        // If what you want is smart point, not use ScopeGuard
        std::unique_ptr<A> a(new A()); // expect delete a when outside
        std::cout << "do something in Fun1" << std::endl;
    }
};

int main()
{
    C c;
    c.Fun1(); std::cout << "------------------------" << std::endl;
    c.Fun2(); std::cout << "------------------------" << std::endl;
    c.Fun3(); std::cout << "------------------------" << std::endl;
    c.Fun4(); std::cout << "------------------------" << std::endl;

    return 0;
}
