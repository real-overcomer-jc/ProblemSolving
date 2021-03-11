#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;

int solution(string begin, string target, vector<string> words) {
    map<string,bool> wordMap;
    for (auto& word : words) {
        wordMap[word] = true;
    }
    if (!wordMap[target]) return 0;
    
    map<string,bool> processed;
    queue<pair<string,int>> q;
    q.push({begin,0});
    while (!q.empty()) {
        pair<string,int> here = q.front(); q.pop();
        string& s = here.first;
        int phase = here.second;
        
        for (int i = 0; i < s.size(); ++i) {
            char origin = s[i];
            for (int j = 0; j < 26; ++j) {
                s[i] = 'a'+j;
                if (s == target) {
                    return phase+1;
                } else if (!processed[s] && wordMap[s]) {
                    q.push({s,phase+1});
                    processed[s] = true;
                }
            }
            s[i] = origin;
        }
    }
    return 0;
}
