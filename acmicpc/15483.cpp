#include <iostream>

using namespace std;

int dp[1001][1001];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    string s1, s2;
    cin >> s1 >> s2;
    
    dp[0][0] = 0;
    for (int i = 1; i <= s1.size(); ++i)
        dp[i][0] = i;
    for (int i = 1; i <= s2.size(); ++i)
        dp[0][i] = i;

    for (int i = 1; i <= s1.size(); ++i) {
        for (int j = 1; j <= s2.size(); ++j) {
            if (s1[i-1] == s2[j-1]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j],dp[i][j-1])) + 1; 
        }
    }
    cout << dp[s1.size()][s2.size()] << endl;  
}
