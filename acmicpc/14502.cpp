#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <tuple>

#define y first
#define x second

using namespace std;
using Point = pair<int,int>;

const int INF = numeric_limits<int>::max();
const int dy[] = {1,0,-1,0};
const int dx[] = {0,1,0,-1};

int N, M;

vector<vector<int>> findShortestPath(const vector<vector<int>>& board, const vector<Point>& virusLocations) {
    vector<vector<int>> dist(N, vector<int>(M, INF));
    queue<Point> q;
    for (auto& p : virusLocations) q.push({p.y, p.x}), dist[p.y][p.x] = 0;
    while (!q.empty()) {
        int y, x;
        tie(y,x) = q.front(); q.pop();
        for (int i = 0; i < 4; ++i) {
            int ny = y + dy[i], nx = x + dx[i];
            if (ny < 0 || ny >= N || nx < 0 || nx >= M || board[ny][nx]) continue;
            if (dist[ny][nx] != INF) continue;
            dist[ny][nx] = dist[y][x] + 1;
            q.push({ny,nx});
        }
    }
    return dist;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    cin >> N >> M;
    vector<vector<int>> board(N, vector<int>(M,0));
    vector<Point> emptyBoxes, virusLocations;
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < M; ++x) {
            cin >> board[y][x];
            if (board[y][x] == 0) emptyBoxes.push_back({y,x});
            else if (board[y][x] == 2) virusLocations.push_back({y,x});
        }
    }

    int maxSafeAreaCount = numeric_limits<int>::min();
    vector<Point> picked(3);
    for (int i = 0; i < emptyBoxes.size(); ++i) {
        picked[0] = emptyBoxes[i];
        for (int j = i+1; j < emptyBoxes.size(); ++j) {
            picked[1] = emptyBoxes[j];
            for (int k = j+1; k < emptyBoxes.size(); ++k) {
                picked[2] = emptyBoxes[k];
                for (int l = 0; l < 3; ++l) board[picked[l].y][picked[l].x] = 1;
                
                int safeAreaCount = 0;
                vector<vector<int>> ret = findShortestPath(board, virusLocations);
                for (int y = 0; y < N; ++y) {
                    for (int x = 0; x < M; ++x) {
                        if (ret[y][x] == INF && board[y][x] == 0) ++safeAreaCount;
                    }
                }

                maxSafeAreaCount = max(maxSafeAreaCount, safeAreaCount);
                for (int l = 0; l < 3; ++l) board[picked[l].y][picked[l].x] = 0;
            }
        }
    }

    cout << maxSafeAreaCount << endl;
}
