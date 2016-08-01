// file: assert.cc
// compile: g++ -std=c++11 -o assert assert.cc
#include <stdio.h>

// From GSL library
#define TO_STRING_DELTA(x) #x
#define TO_STRING(x) TO_STRING_DELTA(x)
#define Expects(cond) if(!(cond)) {\
    printf("Precondition (" #cond ") failure at " __FILE__ ": " TO_STRING(__LINE__) "\n"); \
    return 1; \
}
#define Ensures(cond) if(!(cond)) {\
    printf("Postcondition (" #cond ") failure at " __FILE__ ": " TO_STRING(__LINE__) "\n"); \
    return 1; \
}

int increment(int* p, int n)
{
    Expects(p != NULL);
    for (int i=0; i<n; ++i) ++p[i];
    return 0;
}

int area(int height, int width, int s)
{
    auto res = height * width;
    Ensures(res > 0);
    s = res;
    return 0;
}

int main ( )
{
    int ret = 0;
    ret = increment(NULL, 10);

    int h = 0x7FFFFFFF;
    int w = 2;
    int s = 0;
    ret = area(h, w, s);
    Ensures(0 == ret);

    return 0;
}
