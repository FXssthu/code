#include <iostream>
#include "sum.h"
using namespace std;
int func(int a, const int b = 10, int c = 12)
{
    return a + b + c;
}
int main()
{
    cout << "Result:" << func(1, 20, 30) << endl;

    return 0;
}