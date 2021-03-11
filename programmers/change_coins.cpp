#include <cstring>
#include <vector>

using namespace std;

const int MOD = 1000000007;

//dp[i][j] = i번째 동전까지 사용하여 j원을 거슬러 줄 수 있는 방법의 수
//dp[i][j] = dp[i-1][j] + dp[i][j-money[i]]
/*int dp[101][100001];

int solution(int n, vector<int> money) {
    memset(dp, 0, sizeof dp);
    
    dp[0][0] = 1;
    for (int i = money[0]; i <= n; i+=money[0]) {
        dp[0][i] = 1;
    }
    
    for (int i = 1; i < money.size(); ++i) {
        for (int j = 0; j <= n; ++j) {
            dp[i][j] = dp[i-1][j];
            if (money[i] <= j) dp[i][j] += dp[i][j-money[i]];
        }
    }
    return dp[money.size()-1][n];
}*/

int dp[100001];

int solution(int n, vector<int> money) {
    memset(dp, 0, sizeof dp);
    
    dp[0] = 1;
    for (int i = money[0]; i <= n; i+=money[0]) {
        dp[i] = 1;
    }
    
    for (int i = 1; i < money.size(); ++i) {
        for (int j = 0; j <= n; ++j) {
            if (money[i] <= j) dp[j] = (dp[j] + dp[j-money[i]]) % MOD;
        }
    }
    return dp[n];
}
