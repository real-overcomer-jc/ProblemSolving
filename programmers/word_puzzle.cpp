#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

const int INF = 987654321;

int dp[20002];

int solution(vector<string> strs, string t) {
    for (int i = 0; i < t.size()+1; ++i)
        dp[i] = INF;
    
    dp[0] = 0;
    for (int i = 0; i < t.size(); ++i) {
        for (auto& str : strs) {
            if (i + 1 < str.size()) continue;
            if (strncmp(t.c_str() + i-str.size()+1, str.c_str(), str.size())) continue;
            dp[i+1] = min(dp[i+1], 1 + dp[i+1-str.size()]);
        }
    }
    return dp[t.size()] == INF ? -1 : dp[t.size()];
}
