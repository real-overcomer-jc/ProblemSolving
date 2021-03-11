#include <string>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

set<vector<string>> blockListSet;

bool match(const string& s1, const string& s2) {
    if (s1.size() != s2.size()) return false;
    for (int i = 0; i < s1.size(); ++i) {
        if (s1[i] == '*' || s2[i] == '*') continue;
        if (s1[i] != s2[i]) return false; 
    }
    return true;
}

int permutations(const vector<string>& user_id, const vector<string>& banned_id, int used, vector<string>& picked) {
    if (picked.size() == banned_id.size()) {
        for (int i = 0; i < banned_id.size(); ++i) {
            if (!match(picked[i],banned_id[i])) return 0;
        }
        
        vector<string> ordered = picked;
        sort(ordered.begin(), ordered.end());
        if (!blockListSet.empty()) { 
            auto it = blockListSet.find(ordered);
            if (it != blockListSet.end()) return 0;
        }
        blockListSet.insert(ordered);
        return 1;
    }
    
    int ret = 0;
    for (int i = 0; i < user_id.size(); ++i) {
        if (used & (1<<i)) continue;
        picked.push_back(user_id[i]);
        ret += permutations(user_id, banned_id, used | (1<<i), picked);
        picked.pop_back();
    }
    return ret;
}

int solution(vector<string> user_id, vector<string> banned_id) {
    blockListSet.clear();
    vector<string> picked;
    return permutations(user_id, banned_id, 0, picked);
}
