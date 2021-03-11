#include <string>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;
using TruckInfo = pair<int,int>;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    queue<TruckInfo> q;
    int i = 0, sumWeights = 0, clock = 0;
    while (i < truck_weights.size() || !q.empty()) {
        if (!q.empty() && clock - q.front().first == bridge_length) {
            sumWeights -= q.front().second;
            q.pop();
        } 
        if (i < truck_weights.size() && sumWeights + truck_weights[i] <= weight) {
            sumWeights += truck_weights[i];
            q.push({clock,truck_weights[i]});
            ++i;
        }
        ++clock;
    }
    return clock;
}
