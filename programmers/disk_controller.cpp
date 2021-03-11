#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
using JobInfo = pair<int,int>;

int solution(vector<vector<int>> jobs) {
    sort(jobs.begin(), jobs.end());
    
    priority_queue<JobInfo, vector<JobInfo>, greater<JobInfo>> waitQueue;
    int endTime = 0, totalTime = 0, i = 0;
    while (i < jobs.size() || !waitQueue.empty()) {
        if (i < jobs.size() && jobs[i][0] <= endTime) {
            waitQueue.push({jobs[i][1],jobs[i][0]});
            ++i;
        } else {
            if (!waitQueue.empty()) {
                auto jobInfo = waitQueue.top(); waitQueue.pop();
                endTime += jobInfo.first;
                totalTime += endTime - jobInfo.second;
            } else if (i < jobs.size()) {
                endTime = jobs[i][0] + jobs[i][1];
                totalTime += jobs[i][1];
                ++i;
            }
        }
    }
    return totalTime / jobs.size();
}
