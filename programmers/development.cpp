#include <string>
#include <vector>
#include <limits>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> ret;
    int maxRemainingDays = numeric_limits<int>::min();
    for (int i = 0; i < progresses.size(); ++i) {
        int remainingDays = (100-progresses[i]+speeds[i]-1)/speeds[i];
        if (maxRemainingDays < remainingDays) {
            ret.push_back(1);
            maxRemainingDays = remainingDays;
        } else {
            ++ret.back();
        }
    }
    return ret;
}
