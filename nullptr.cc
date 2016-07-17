// file: nullptr.cc
// compile: g++ -std=c++11 -o nullptr nullptr.cc

#include <cstddef> // for NULL

void test(int a)
{
}

void test_NULL()
{
    int* p = NULL;
    *p = 2;
    int a = NULL;  // just warning, success to compile

    test(NULL);    // just warning, success to compile
}

void test_nullptr()
{
    int* p = nullptr;
    *p = 2;
    //test(nullptr); // fail to compile
}

int main(int argc, char* argv[])
{
    test_nullptr();

    return 0;
}
