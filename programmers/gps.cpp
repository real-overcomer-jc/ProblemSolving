#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 987654321;

//dp[i][j] = i번째 거점을 j로 변경했을때 i번째 거점까지의 최소변경횟수
//dp[i][j] = min(dp[i-1][j], dp[i][p] + (gps_log[i] == j ? 0 : 1));
int dp[202][202];
vector<vector<int>> adj;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, int m, vector<vector<int>> edge_list, int k, vector<int> gps_log) {
    adj = vector<vector<int>>(n+1, vector<int>(n+1,0));
    for (auto& edge : edge_list) {
        int u = edge[0], v = edge[1];
        adj[u][v] = adj[v][u] = 1;
    }
    
    fill(&dp[0][0], &dp[201][202], INF);
    dp[0][gps_log[0]] = 0;
    for (int i = 1; i < k; ++i) {
        for (int j = 1; j <= n; ++j) {
            int inc = (gps_log[i] == j ? 0 : 1);
            dp[i][j] = dp[i-1][j] + inc;
            for (int p = 1; p <= n; ++p) {
                if (adj[p][j]) {
                    dp[i][j] = min(dp[i][j], dp[i-1][p] + inc);
                }
            }
        }
    }
    return dp[k-1][gps_log[k-1]] >= INF ? -1 : dp[k-1][gps_log[k-1]];
}
