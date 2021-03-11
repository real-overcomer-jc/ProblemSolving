#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int N, K, dp[10001];

int main() {
    cin >> N >> K;

    int coins[N];
    for (int i = 0; i < N; ++i) {
        cin >> coins[i];
    }

    memset(dp, 0, sizeof dp);
    dp[0] = 1;
    for (int i = 0; i < N; ++i) {
        for (int j = 1; j <= K; ++j) {
            if (coins[i] <= j) dp[j] += dp[j-coins[i]];
        }
    }
    cout << dp[K] << endl;
}
