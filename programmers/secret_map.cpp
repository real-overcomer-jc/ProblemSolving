#include <string>
#include <vector>

using namespace std;

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
    vector<int> merged;
    for (int y = 0; y < n; ++y) {
        merged.push_back(arr1[y] | arr2[y]);
    }
    
    vector<string> ret(n, string(n,' '));
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            ret[y][x] = (merged[y] & (1 << (n-1-x))) ? '#' : ' ';
        }
    }
    return ret;
}
