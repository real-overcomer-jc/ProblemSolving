#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct MCMF {
    struct Edge {
        int v, cap, cost, rev;
    };

    int N, S, T;
    vector<vector<Edge>> adj;
    vector<int> prev, edgeIdx, dist;
    vector<bool> inQ;

    MCMF(int N_, int S_, int T_) : N(N_), S(S_), T(T_), 
    adj(N_), prev(N_), edgeIdx(N_), dist(N_), inQ(N_) {}

    void addEdge(int u, int v, int cap, int cost) {
        adj[u].push_back({v, cap, cost, (int)adj[v].size()});
        adj[v].push_back({u, 0, -cost, (int)adj[u].size()-1});
    }

    int spfa() {
        fill(prev.begin(), prev.end(), -1);
        fill(dist.begin(), dist.end(), INF);
        fill(inQ.begin(), inQ.end(), false);

        queue<int> q;
        q.push(S);
        dist[S] = 0;
        prev[S] = S;
        inQ[S] = true;
        while (!q.empty()) {
            int here = q.front(); q.pop();
            inQ[here] = false;

            for (int i = 0; i < adj[here].size(); ++i) {
                auto& edge = adj[here][i];
                if (edge.cap > 0 && dist[here] + edge.cost < dist[edge.v]) {
                    dist[edge.v] = dist[here] + edge.cost;
                    prev[edge.v] = here;
                    edgeIdx[edge.v] = i;
                    if (!inQ[edge.v]) {
                        q.push(edge.v);
                        inQ[edge.v] = true;
                    }
                }
            }
        }
        return prev[T] != -1;
    }

    pair<int,int> run() {
        int totalFlow = 0, totalCost = 0;
        while (spfa()) {
            int amount = numeric_limits<int>::max();
            for (int p = T; p != S; p = prev[p]) {
                auto& edge = adj[prev[p]][edgeIdx[p]];
                amount = min(amount, edge.cap);
            }

            int costSum = 0;
            for (int p = T; p != S; p = prev[p]) {
                auto& edge = adj[prev[p]][edgeIdx[p]];
                edge.cap -= amount;
                adj[edge.v][edge.rev].cap += amount;
                costSum += edge.cost;
            }

            totalFlow += amount;
            totalCost += costSum * amount;
        }
        return {totalFlow, totalCost};
    }    
};

int main() {
    int N, M;
    cin >> N >> M;

    int S = N+M, T = S+1;
    MCMF mcmf(N+M+2, S, T);

    for (int i = 0; i < N; ++i) {
        mcmf.addEdge(S, i, 1, 0);
    }

    for (int i = 0; i < M; ++i) {
        mcmf.addEdge(N+i, T, 1, 0);
    }

    int count, v, cost;
    for (int i = 0; i < N; ++i) {
        cin >> count;
        for (int j = 0; j < count; ++j) {
            cin >> v >> cost;
            mcmf.addEdge(i, N+v-1, INF, cost);
        }
    }

    pair<int,int> ret = mcmf.run();
    cout << ret.first << endl;
    cout << ret.second << endl;
}
