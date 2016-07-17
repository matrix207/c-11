// file: lambda.cc
// compile: g++ -std=c++11 -o lambda lambda.cc

#include <iostream>
#include <vector>
#include <algorithm> // for_each
#include <functional> // lambda

using namespace std;

void test_lambda()
{
    vector<int> iv{5, 4, 3, 2, 1};
    int a = 2, b = 1;

    for_each(iv.begin(), iv.end(), [b](int &x){cout<<(x + b)<<endl;});

    for_each(iv.begin(), iv.end(), [=](int &x){x *= (a + b);});

    for_each(iv.begin(), iv.end(), [=](int &x)->int{return x * (a + b);});
}

int main(int argc, char* argv[])
{
    test_lambda();

    return 0;
}
