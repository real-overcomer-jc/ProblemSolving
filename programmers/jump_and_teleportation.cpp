#include <iostream>
using namespace std;

int count(int n) {
    if (n == 0) return 0;
    return (n % 2 == 0) ? count(n/2) : 1 + count((n-1)/2);
}

int solution(int n)
{
    return count(n);
}
