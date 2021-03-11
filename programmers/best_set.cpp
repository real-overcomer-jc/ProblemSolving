#include <vector>

using namespace std;

vector<int> solution(int n, int s) {
    int quotient = s / n;
    if (quotient == 0) return {-1};
    
    vector<int> ret(n, quotient);
    int remainder = s % n;
    for (int i = 0; i < remainder; ++i) {
        ++ret[n-1-i];
    }
    return ret;
}
