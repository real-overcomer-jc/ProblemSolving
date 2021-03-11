#include <iostream>
#include <vector>
#include <cstring>

#define newline '\n'

using namespace std;

const int MOD = 1e9;
int dp[101][10];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int N;
    cin >> N;

    memset(dp, 0, sizeof dp);
    for (int c = 1; c <= 9; ++c) {
        dp[0][c] = 1;
    }

    for (int i = 1; i < N; ++i) {
        for (int c = 0; c <= 9; ++c) {
            dp[i][c] = (dp[i][c] + ((c > 0) ? dp[i-1][c-1] : 0)) % MOD;
            dp[i][c] = (dp[i][c] + ((c < 9) ? dp[i-1][c+1] : 0)) % MOD;
        }
    }

    int ret = 0;
    for (int c = 0; c <= 9; ++c) {
        ret = (ret + dp[N-1][c]) % MOD;
    }
    cout << ret << endl;
}
