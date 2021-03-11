#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool evaluateKey(const vector<vector<string>>& relation, int keyColumns) {
    vector<vector<string>> filteredRelation;
    for (int i = 0; i < relation.size(); ++i) {
        vector<string> filteredRecord;
        for (int j = 0; j < relation[i].size(); ++j) {
            if (keyColumns & (1<<j)) filteredRecord.push_back(relation[i][j]);
        }
        auto it = find(filteredRelation.begin(), filteredRelation.end(), filteredRecord);
        if (it != filteredRelation.end()) return false;
        filteredRelation.push_back(filteredRecord);
    }
    return true;
}

int solution(vector<vector<string>> relation) {
    const int n = relation[0].size();
    vector<vector<int>> keyList(n+1,vector<int>());
    for (int set = 1; set < (1<<n); ++set) {
        int bitCount = __builtin_popcount(set);
        keyList[bitCount].push_back(set);
    }
    
    vector<int> candidateKeyList;
    for (int i = 1; i < keyList.size(); ++i) {
        for (int j = 0; j < keyList[i].size(); ++j) {
            int candidate = keyList[i][j];
            
            auto pred = [&] (int candidateKey) {
                return (candidate & candidateKey) == candidateKey;
            };
            auto it = find_if(candidateKeyList.begin(), candidateKeyList.end(), pred);
            if (it != candidateKeyList.end()) continue;
            
            if (evaluateKey(relation, candidate)) candidateKeyList.push_back(candidate);
        }
    }
    return candidateKeyList.size();
}
