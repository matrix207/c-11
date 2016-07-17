// file: for_each.cc
// compile: g++ -std=c++11 -o for_each for_each.cc
// from <http://www.cnblogs.com/yejianfei/archive/2012/10/19/2731337.html>
#include <iostream>
#include <cstdlib>
#include <algorithm>   // sort,for_each
#include <functional>  // function

using namespace std;

#ifndef _countof
#define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#endif

int main ( )
{
    int a[] = {1,2,5,9,52,6,3,14};
    function <bool (const int & , const int &)> compare;
    auto output = [](int n)->void{ cout << n << endl; };
    // C++11标准中， auto 关键字新义，任意类型，类型由初始化表达式确定
    // “[](int n)->void{ cout << n << endl; }”是Lambda表达式

    cout << "升序排序" << endl;
    compare = []( const int & a , const int & b )->bool { return a < b; };
    sort( a, a+_countof(a), compare  );
    for_each( a, a+_countof(a), output );
    cout << endl;

    cout << "降序排序" << endl;
    compare = []( const int & a , const int & b )->bool { return b < a; };
    sort( a, a+_countof(a), compare  );
    for_each( a, a+_countof(a), output );
    cout << endl;

    return EXIT_SUCCESS;
}
