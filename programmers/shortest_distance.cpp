#include <vector>
#include <queue>
#include <tuple>

using namespace std;
using PathInfo = pair<int,int>;

const int INF = 987654321;

const int dy[] = {1,0,-1,0};
const int dx[] = {0,1,0,-1};

int solution(vector<vector<int> > maps)
{
    int H = maps.size(), W = maps[0].size();
    vector<vector<int>> dist(H,vector<int>(W,INF));
    queue<PathInfo> q;
    q.push({0,0});
    dist[0][0] = 1;
    while (!q.empty()) {
        int y, x;
        tie(y, x) = q.front(); q.pop();
        for (int i = 0; i < 4; ++i) {
            int ny = y+dy[i], nx = x+dx[i];
            if (ny < 0 || ny >= H || nx < 0 || nx >= W || !maps[ny][nx]) continue;
            if (ny == H-1 && nx == W-1) return dist[y][x]+1;
            if (dist[ny][nx] != INF) continue;
            dist[ny][nx] = dist[y][x]+1;
            q.push({ny,nx});
        }
    }
    return -1;
}
