#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using namespace std;
using Edge = pair<int,int>;

const int INF = numeric_limits<int>::max();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<Edge>> adj(N+1);
    //adj.clear();
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
    }

    vector<long long> dist(N+1,INF), count(N+1,0);
    vector<bool> inQ(N+1,false);
    queue<int> q;
    bool hasMinusCycle = false;

    q.push(1);
    dist[1] = 0;
    count[1] = 1;
    inQ[1] = true;
    while (!q.empty()) {
        int here = q.front(); q.pop();
        inQ[here] = false;

        for (auto edge : adj[here]) {
            int there = edge.first, cost = edge.second;
            if (dist[here] + cost < dist[there]) {
                dist[there] = dist[here] + cost;
                if (!inQ[there]) {
                    if (++count[there] == N) {
                        hasMinusCycle = true;
                        break;
                    }
                    q.push(there);
                    inQ[there] = true;
                }
            }
        }
        if (hasMinusCycle) break;
    }

    if (hasMinusCycle) {
        cout << -1 << endl;
    } else {
        for (int i = 2; i <= N; ++i) {
            if (dist[i] == INF) cout << -1 << endl;
            else cout << dist[i] << endl;
        }
    }
}
