#include <iostream>
#include <cstring>
#include <limits>

using namespace std;

int cache[1000001];

int count(int n) {
    if (n == 1) return 0;

    int& ret = cache[n];
    if (ret != -1) return ret;

    ret = numeric_limits<int>::max();
    if (n % 3 == 0) ret = min(ret, 1 + count(n/3));
    if (n % 2 == 0) ret = min(ret, 1 + count(n/2));
    ret = min(ret, 1 + count(n-1));
    return ret;
}

int main() {
    memset(cache, -1, sizeof cache);
    int n;
    cin >> n;
    cout << count(n) << endl;
}
