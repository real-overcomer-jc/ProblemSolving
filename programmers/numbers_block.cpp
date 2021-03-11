#include <string>
#include <vector>
#include <cmath>

using namespace std;

vector<int> solution(long long begin, long long end) {
    vector<int> ret(end-begin+1,1);
    for (int i = begin; i <= end; ++i) {
        int factor = 1;
        for (int j = 2; j <= sqrt(i); ++j) {
            if (i%j == 0 && i/j <= 10000000) {
                factor = i/j;
                break;
            }
        }
        ret[i-begin] = factor;
    }
    if (begin == 1) ret[0] = 0;
    return ret;
}
