#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

int solution(int n, vector<vector<int>> edge) {
    vector<vector<int>> adj(n+1, vector<int>(n+1,0));
    for (auto& e : edge) {
        int u = e[0], v = e[1];
        adj[u][v] = adj[v][u] = 1;
    }
    
    vector<int> dist(n+1,-1);
    queue<int> q;
    q.push(1);
    dist[1] = 0;
    while (!q.empty()) {
        int here = q.front(); q.pop();
        for (int there = 1; there <= n+1; ++there) {
            if (adj[here][there] && dist[there] == -1) {
                dist[there] = dist[here] + 1;
                q.push(there);
            }
        }
    }
    
    sort(dist.begin(), dist.end(), greater<int>());
    int count = 1;
    for (int i = 1; i < dist.size(); ++i) {
        if (dist[i-1] == dist[i]) ++count;
        else break;
    }
    return count;
}
