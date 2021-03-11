#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int dy[] = {-1,0};
const int dx[] = {0,-1};

int N, M, K;
int dp[16][16];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    cin >> N >> M >> K;
    memset(dp, 0, sizeof dp);
    dp[0][0] = 1;
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < M; ++x) {
            for (int i = 0; i < 2; ++i) {
                int ny = y + dy[i], nx = x + dx[i];
                if (ny < 0 || ny >= N || nx < 0 || nx >= M) continue;
                dp[y][x] += dp[ny][nx];
            }
        }
    }

    if (K > 0) {
        int row = (K-1)/M, column = (K-1)%M;  
        int ret = dp[row][column] * dp[N-1-row][M-1-column];
        cout << ret << endl;
    } else {
        cout << dp[N-1][M-1] << endl;
    }
}
