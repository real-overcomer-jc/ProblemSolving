#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const long long INF = 1LL << 31;
const int dy[] = {1,0,-1,0};
const int dx[] = {0,1,0,-1};

long long dp[51][51][2501];

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, int s, vector<vector<int>> time_map) {
    int move_distance = 0;
    int sum_of_talk_time = 0;
    
    fill(&dp[0][0][0], &dp[50][50][2501], INF);
    dp [0][0][0] = 0;
    for (int d = 1; d < 2501; ++d) {
        for (int y = 0; y < m; ++y) {
            for (int x = 0; x < n; ++x) {
                if (time_map[y][x] == -1) continue;
                for (int i = 0; i < 4; ++i) {
                    int ny = y + dy[i], nx = x + dx[i];
                    if (ny < 0 || ny >= m || nx < 0 || nx >= n) continue;
                    //if (dp[ny][nx][d-1] == INF) continue;
                    if (dp[ny][nx][d-1] + time_map[y][x] > (long long)s) continue;
                    dp[y][x][d] = min(dp[y][x][d], dp[ny][nx][d-1] + time_map[y][x]);
                }
            }
        }
    }
    
    for (int d = 0; d < 2501; ++d) {
        if (dp[m-1][n-1][d] != INF) {
            move_distance = d;
            sum_of_talk_time = (int)dp[m-1][n-1][d];
            break;
        }
    }
    
    vector<int> answer(2);
    answer[0] = move_distance;
    answer[1] = sum_of_talk_time;
    
    return answer;
}
