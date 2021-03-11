#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include <tuple>

#define y first
#define x second

using namespace std;
using Point = pair<int,int>;
using PathInfo = tuple<int,int,int>;

const int INF = numeric_limits<int>::max();
const int dy[] = {1,0,-1,0};
const int dx[] = {0,1,0,-1};

int N, M;

int findShortestDistance(const vector<string>& board, const vector<Point>& waterLocations, const Point& startLocation, const Point& targetLocation) {
    vector<string> table = board;
    vector<vector<int>> dist(N, vector<int>(M,INF));
    queue<PathInfo> q;
    for (auto& p : waterLocations) {
        table[p.y][p.x] = 'X';
        q.push({1,p.y,p.x});
    }
    q.push({0,startLocation.y, startLocation.x});
    dist[startLocation.y][startLocation.x] = 0;
    while(!q.empty()) {
        int type, y, x;
        tie(type, y, x) = q.front(); q.pop();
        for (int i = 0; i < 4; ++i) {
            int ny = y + dy[i], nx = x + dx[i];
            if (ny < 0 || ny >= N || nx < 0 || nx >= M || table[ny][nx] == 'X') continue;
            if (type == 1 && dist[ny][nx] == INF && table[ny][nx] != 'D') {
                table[ny][nx] = 'X';
                q.push({1,ny,nx});
            } else if (type == 0 && dist[ny][nx] == INF) {
                dist[ny][nx] = dist[y][x] + 1;
                q.push({0,ny,nx});
            }
        }
    }
    return dist[targetLocation.y][targetLocation.x];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    cin >> N >> M;
    vector<string> board(N, string(M,' '));
    vector<Point> waterLocations;
    Point startLocation, targetLocation;
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < M; ++x) {
            cin >> board[y][x];
            if (board[y][x] == '*') waterLocations.push_back({y,x});
            else if (board[y][x] == 'S') startLocation.y = y, startLocation.x = x;
            else if (board[y][x] == 'D') targetLocation.y = y, targetLocation.x = x;
        }
    }

    int ret = findShortestDistance(board, waterLocations, startLocation, targetLocation);
    if (ret != INF) cout << ret << endl;
    else cout << "KAKTUS" << endl;
}

