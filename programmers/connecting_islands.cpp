
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

class DisjointSet {
private:    
    vector<int> parent, rank;
public:
    DisjointSet(int n): parent(n), rank(n,0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    
    int find(int u) {
        if (parent[u] == u) return u;
        return parent[u] = find(parent[u]);
    }
    
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (rank[u] > rank[v]) swap(u,v);
        parent[u] = v;
        if (rank[u] == rank[v]) ++rank[v];
        return true;
    }
};

int solution(int n, vector<vector<int>> costs) {
    vector<pair<int,vector<int>>> edges;
    for (auto& edge : costs) {
        edges.push_back({edge[2],edge});
    }
    sort(edges.begin(), edges.end());
    
    int total = 0;
    DisjointSet set(n);
    for (int i = 0; i < edges.size(); ++i) {
        vector<int>& edge = edges[i].second;
        if (set.merge(edge[0], edge[1])) {
            total += edge[2];
        }
    }
    return total;
}
