#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();
const int dy[] = {1,0,-1,0};
const int dx[] = {0,1,0,-1};

int dp[25][25][625][4];

int solution(vector<vector<int>> board) {
    const int n = board.size();
    fill(&dp[0][0][0][0], &dp[24][24][624][4], INF);
    for (int dir = 0; dir < 4; ++dir) 
        dp[0][0][0][dir] = 0;
    
    for (int d = 1; d < n*n; ++d) {
        for (int y = 0; y < n; ++y) {
            for (int x = 0; x < n; ++x) {
                for (int dir = 0; dir < 4; ++dir) {
                    for (int i = 0; i < 4; ++i) {
                        if (dir == i) continue;
                        int ny = y + dy[i], nx = x + dx[i];
                        if (ny < 0 || ny >= n || nx < 0 || nx >= n || board[y][x]) continue;
                        int ri = (i+2)%4;
                        if (dp[ny][nx][d-1][ri] == INF) continue;
                        if (dy[ri]*dy[dir] + dx[ri]*dx[dir] == 0) 
                            dp[y][x][d][dir] = min(dp[y][x][d][dir], dp[ny][nx][d-1][ri] + 600);
                        else
                            dp[y][x][d][dir] = min(dp[y][x][d][dir], dp[ny][nx][d-1][ri] + 100);
                    }
                }
            }
        }
    } 
    
    int minCost = INF;
    for (int d = 0; d < n*n; ++d) {
        for (int dir = 0; dir < 4; ++dir) {
            minCost = min(minCost, dp[n-1][n-1][d][dir]); 
        }
    }
    return minCost;
}
