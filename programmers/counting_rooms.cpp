#include <string>
#include <vector>
#include <map>

#define y first
#define x second

using namespace std;
using Point = pair<double,double>;

const int dy[] = {-1,-1,0,1,1,1,0,-1};
const int dx[] = {0,1,1,1,0,-1,-1,-1};

map<Point,vector<Point>> adj;
map<Point,bool> visited;
map<Point,map<Point,bool>> passed;

int roomCounter;

void dfs(Point here) {
    visited[here] = true;
    for (Point& there : adj[here]) {
        if (passed[here][there]) continue;
        passed[here][there] = passed[there][here] = true;
        
        if (!visited[there]) {
            dfs(there);
        } else {
            ++roomCounter;
        }
    }
}

int solution(vector<int> arrows) {
    Point cur{0,0};
    for (int dir : arrows) {
        Point next = {cur.y + dy[dir], cur.x + dx[dir]};
        if (dir == 1 || dir == 3 || dir == 5 || dir == 7) {
            Point half = {cur.y + dy[dir]/2.0, cur.x + dx[dir]/2.0};
            adj[cur].push_back(half);
            adj[half].push_back(next);
        } else {
            adj[cur].push_back(next);
        }
        cur = next;
    }
    
    roomCounter = 0;
    dfs({0,0});
    return roomCounter;
}
