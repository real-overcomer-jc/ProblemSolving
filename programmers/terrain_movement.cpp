#include <string>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const int dy[] = {1,0,-1,0};
const int dx[] = {0,1,0,-1};
const int INF = numeric_limits<int>::max();

int N;
int area;
vector<vector<int>> visited;
vector<vector<int>> costs;

struct DisjointSet {
    vector<int> parent, rank;
    
    DisjointSet(int n) : parent(n), rank(n,0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    
    int find (int u) {
        if (parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }
    
    int merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return 0;
        
        if (rank[u] > rank[v]) swap(u,v);
        parent[u] = v;
        if (rank[u] == rank[v]) ++rank[v];
        return 1;
    }
};

bool inRange(int y, int x) {
    return (0 <= y && y < N) && (0 <= x && x < N);
}

void dfs(const vector<vector<int>>& land, int y, int x, int height) {
    visited[y][x] = area;
    for (int i = 0; i < 4; ++i) {
        if (!inRange(y+dy[i],x+dx[i])) continue;
        if (visited[y+dy[i]][x+dx[i]] != -1) continue;
        
        int diff = abs(land[y][x]-land[y+dy[i]][x+dx[i]]);
        if (diff <= height) {
            dfs(land, y+dy[i], x+dx[i], height);
        }
    }
}

void dfsAll(const vector<vector<int>>& land, int height) {
    ::area = 0;
    visited = vector<vector<int>>(N,vector<int>(N,-1));
    
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < N; ++x) {
            if (visited[y][x] == -1) {
                dfs(land,y,x,height);
                ++area;
            }
        }
    }
}

int solution(vector<vector<int>> land, int height) {
    ::N = land.size();
    
    dfsAll(land, height);
    
    vector<pair<int,pair<int,int>>> edges;
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < N; ++x) {
            int area1 = visited[y][x];
            for (int i = 0; i < 4; ++i) {
                if (!inRange(y+dy[i],x+dx[i])) continue;
                int area2 = visited[y+dy[i]][x+dx[i]];
                if (area1 != area2) {
                    edges.push_back({abs(land[y][x]-land[y+dy[i]][x+dx[i]]),{area1,area2}});
                }
            }
        }
    }
    sort(edges.begin(), edges.end());
    
    int ret = 0;
    DisjointSet set(area);
    for (auto& edge : edges) {
        int cost = edge.first, u = edge.second.first, v = edge.second.second;
        if (set.merge(u,v)) ret += cost;
    }
    return ret;
}
