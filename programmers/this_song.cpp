#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> splitString(const string& s) {
    vector<string> ret;
    auto begin = s.find_first_not_of(",");
    auto end = string::npos;
    while (begin != string::npos) {
        end = s.find_first_of(",", begin);
        if (end == string::npos) {
            end = s.size();
        }
        ret.push_back(s.substr(begin, end-begin));
        begin = s.find_first_not_of(",", end);
    }
    return ret;
}

int toTimepoint(string time) {
    int hour = stoi(time.substr(0,2));
    int min = stoi(time.substr(3,2));
    return hour * 60 + min;
}

string playMusic(const string& score, int time) {
    string ret;
    int len = score.size(), i = 0;
    for (int t = 0; t < time; ++t) {
        ret.push_back(score[i]);
        if (i+1 < len && score[i+1] == '#') {
            ret.push_back(score[i+1]);
            ++i;
        } 
        i = (i+1)%len;
    }
    return ret;
}

string solution(string m, vector<string> musicinfos) {
    vector<pair<string,int>> matched;
    for (int i = 0; i < musicinfos.size(); ++i) {
        vector<string> splited = splitString(musicinfos[i]);
        
        int playTime = toTimepoint(splited[1]) - toTimepoint(splited[0]);
        string playedMusic = playMusic(splited[3], playTime);
        
        auto idx = playedMusic.find(m);
        while (idx != string::npos) {
            if (idx+m.size() < playedMusic.size() && playedMusic[idx+m.size()] == '#') {
                idx = playedMusic.find(m, idx+m.size());
            } else {
                matched.push_back({splited[2],playTime});
                break;
            }
        }
    }
    
    if (matched.empty()) return "(None)";
    if (matched.size() == 1) return matched[0].first;
    
    int longest = matched[0].second;
    string title = matched[0].first;
    for (int i = 1; i < matched.size(); ++i) {
        if (longest < matched[i].second) {
            longest = matched[i].second;
            title = matched[i].first;
        }
    }
    return title;
}
