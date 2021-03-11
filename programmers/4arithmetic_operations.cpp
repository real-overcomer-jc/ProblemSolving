#include <vector>
#include <string>
#include <cstring>
#include <limits>

using namespace std;

int cacheMin[202][202];
int cacheMax[202][202];

int dpMin(const vector<string>& arr, int a, int b);
int dpMax(const vector<string>& arr, int a, int b);

int dpMin(const vector<string>& arr, int a, int b) {
    if (a == b) return stoi(arr[a]);
    
    int& ret = cacheMin[a][b];
    if (ret != -1) return ret;
    
    ret = numeric_limits<int>::max();
    for (int i = a+1; i < b; i+=2) {
        if (arr[i] == "+")
            ret = min(ret, dpMin(arr, a, i-1) + dpMin(arr, i+1, b));
        else
            ret = min(ret, dpMin(arr, a, i-1) - dpMax(arr, i+1, b));
    }
    return ret;
}

int dpMax(const vector<string>& arr, int a, int b) {
    if (a == b) return stoi(arr[a]);
    
    int& ret = cacheMax[a][b];
    if (ret != -1) return ret;
    
    ret = numeric_limits<int>::min();
    for (int i = a+1; i < b; i+=2) {
        if (arr[i] == "+")
            ret = max(ret, dpMax(arr, a, i-1) + dpMax(arr, i+1, b));
        else
            ret = max(ret, dpMax(arr, a, i-1) - dpMin(arr, i+1, b));
    }
    return ret;
}

int solution(vector<string> arr)
{
    memset(cacheMin, -1, sizeof cacheMin);
    memset(cacheMax, -1, sizeof cacheMax);
    return dpMax(arr, 0, arr.size()-1);
}
