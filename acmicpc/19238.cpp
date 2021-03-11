#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <tuple>
#include <limits>
#include <algorithm>

using namespace std;
using PathInfo = tuple<int,int>;

const int INF = numeric_limits<int>::max();
const int dy[] = {-1,0,1,0};
const int dx[] = {0,1,0,-1};

int N, M, F, startY, startX;

vector<vector<int>> calcShortestDistance(const vector<vector<int>>& board, int startY, int startX) {
    vector<vector<int>> dist(N, vector<int>(N,INF));
    queue<PathInfo> q; 
    q.push({startY,startX});
    dist[startY][startX] = 0;
    while (!q.empty()) {
        int y, x;
        tie(y,x) = q.front(); q.pop();
        
        for (int i = 0; i < 4; ++i) {
            int ny = y + dy[i], nx = x + dx[i];
            if (ny < 0 || ny >= N || nx < 0 || nx >= N || board[ny][nx] == 1) continue;
            if (dist[ny][nx] != INF) continue;
            dist[ny][nx] = dist[y][x] + 1;
            q.push({ny,nx});
        }
    }
    return dist;
}

int solution(int N, int M, int F, const vector<vector<int>>& board, int startY, int startX, const vector<vector<int>>& calls) {
    unordered_map<int,bool> processed;
    while (M-- > 0) {
        //select the closest one
        vector<vector<int>> dist = calcShortestDistance(board, startY, startX);
        int minDist = INF, pickedCallNo = -1;
        for (int i = 0; i < calls.size(); ++i) {
            int y = calls[i][0], x = calls[i][1];
            if (!processed[i] && dist[y][x] < minDist) {
                minDist = dist[y][x];
                pickedCallNo = i;
            }
        }
        processed[pickedCallNo] = true;

        if (F < minDist) return -1;
        F -= minDist;

        dist = calcShortestDistance(board, calls[pickedCallNo][0], calls[pickedCallNo][1]);
        int cost = dist[calls[pickedCallNo][2]][calls[pickedCallNo][3]];
        if (F < cost) return -1;
        F += cost;

        startY = calls[pickedCallNo][2], startX = calls[pickedCallNo][3];
    }
    return F;
}

int main() {
    cin >> N >> M >> F;

    vector<vector<int>> board(N, vector<int>(N,0));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> board[i][j];
        }
    }

    cin >> startY >> startX;
    --startY, --startX;

    vector<vector<int>> calls(M, vector<int>(4,0));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < 4; ++j) {
            cin >> calls[i][j]; 
            --calls[i][j];
        }
    }
    sort(calls.begin(), calls.end());

    cout << solution(N,M,F,board,startY,startX,calls) << endl;
}
