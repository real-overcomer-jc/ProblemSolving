using int64 = long long;
const int MOD = 1000000007;

int64 dp[5001];

int solution(int n) {
    dp[0] = 1, dp[2] = 3;
    for (int i = 4; i <= n; i += 2) {
        dp[i] = 0;
        for (int j = 2; j <= i; j += 2) {
            dp[i] = (dp[i] + (dp[i-j] * (j == 2 ? 3 : 2))%MOD)%MOD;
        }
    }
    return dp[n];
}
