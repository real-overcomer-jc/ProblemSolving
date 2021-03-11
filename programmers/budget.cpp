#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> d, int budget) {
    sort(d.begin(), d.end());
    
    int ret = 0;
    for (int i = 0; i < d.size(); ++i) {
        if (budget < d[i]) break;
        budget -= d[i];
        ++ret;
    }   
    return ret;
}
