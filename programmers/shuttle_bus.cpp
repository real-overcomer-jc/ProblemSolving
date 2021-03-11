#include <string>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string solution(int n, int t, int m, vector<string> timetable) {
    vector<int> timepoint(timetable.size());
    auto toTimepoint = [] (string time) {
        int hour = stoi(time.substr(0,2),nullptr,10);
        int min = stoi(time.substr(3,2),nullptr,10);
        return hour * 60 + min;
    };
    transform(timetable.begin(), timetable.end(), timepoint.begin(), toTimepoint);
    sort(timepoint.begin(), timepoint.end());

    vector<pair<int,int>> schedule(n);
    schedule[0] = {0,540};
    for (int i = 1; i < n; ++i) {
        schedule[i] = {schedule[i-1].second+1, schedule[i-1].second+t}; 
    }
    
    vector<vector<int>> wait(n, vector<int>());
    for (int i = 0; i < timepoint.size(); ++i) {
        for (int j = 0; j < n; ++j) {
            int start = schedule[j].first, end = schedule[j].second;
            if (start <= timepoint[i] && timepoint[i] <= end) {
                wait[j].push_back(timepoint[i]);
                break;
            }
        }
    }

    for (int i = 0; i+1 < wait.size(); ++i) {
        if (wait[i].size() > m) {
            wait[i+1].insert(wait[i+1].begin(), wait[i].begin()+m, wait[i].end());
            wait[i].erase(wait[i].begin()+m, wait[i].end());
        }
    }
    
    int lastTimepoint{};
    if (wait[n-1].size() < m) {
        lastTimepoint = schedule[n-1].second;
    } else {
        lastTimepoint = wait[n-1][m-1]-1;
    }

    int hour = lastTimepoint / 60, min = lastTimepoint % 60;
    string strHour = ((hour < 10) ? string("0") : string()) + to_string(hour);
    string strMin = ((min < 10) ? string("0") : string()) + to_string(min);
    return strHour + ":" + strMin;
}
