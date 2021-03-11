#include <iostream>
#include <vector>
#include <cstring>
#include <limits>

using namespace std;

int dp[102][100001]; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, K;
    cin >> N >> K;

    vector<vector<int>> travel(N,vector<int>(4,0));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> travel[i][j];
        }
    }

    memset(dp, 0, sizeof dp);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j <= K; ++j) {
            int walkingTime = travel[i][0], walkingFund = travel[i][1];
            int bikeTime = travel[i][2], bikeFund = travel[i][3];

            dp[i+1][j] = numeric_limits<int>::min();
            if (walkingTime <= j) dp[i+1][j] = max(dp[i+1][j], walkingFund + dp[i][j-walkingTime]);
            if (bikeTime <= j) dp[i+1][j] = max(dp[i+1][j], bikeFund + dp[i][j-bikeTime]);
        }
    }
    cout << dp[N][K] << endl;
}   
