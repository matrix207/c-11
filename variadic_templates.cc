// file: variadic_templates.cc
// compile: g++ -std=c++11 -o variadic_templates variadic_templates.cc
#include <iostream>

using namespace std;

inline void EXPECT_EQ(long exp, long value) {
    if (exp != value) {
        cout << "Compare failed, expect:" << exp << ", real:" << value << endl;
    }
}

template<long N>
struct print_value_as_warning
{
    char operator()() {return N + 256;} // always cause overflow
};

//////////////////////////////////////////////////////////////////////
// Print
template<typename Head>
void Print(Head head) {
    cout<< head <<endl;
}

template<typename Head, typename... Tail>
void Print(Head head, Tail... tail) {
    cout<< head <<endl;
    Print(tail...);
}

void test_print()
{
    Print(1, -100, 1.5, 1234567890, "C++11");
}

//////////////////////////////////////////////////////////////////////
// Add
template <long ... Args> class vsum;

template <long d, long ... Args>
class vsum<d, Args...> {
public:
    static const long value = d + vsum<Args...>::value;
};

template <>
class vsum<> {
public:
    static const long value = 0;
};

void test_sum()
{
    long s = vsum<>::value;             EXPECT_EQ(0, s);
    s = vsum<5, 5>::value;              EXPECT_EQ(10, s);
    s = vsum<5, 2, 3>::value;           EXPECT_EQ(10, s);
    s = vsum<3, 3, 1, 3>::value;        EXPECT_EQ(10, s);
    s = vsum<2, 2, 2, 2, -1, 3>::value; EXPECT_EQ(10, s);
}

// prove that sum calculation occurred on compile time
void test_sum_run_on_compile_time()
{
    // When do compilation, will got such message：
    // In instantiation of ‘char print_size_as_warning<N>::operator()() [with long N = 125]’:
    print_value_as_warning<vsum<100,25>::value>()();
}

//////////////////////////////////////////////////////////////////////
// main
int main(int argc, char* argv[])
{
    test_print();
    test_sum();
    return 0;
}

