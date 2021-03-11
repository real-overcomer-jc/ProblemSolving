#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

struct MaxFlow {
    struct Edge {
        int v, cap, rev;
    };

    int N, S, T;
    vector<vector<Edge>> adj;
    vector<int> level, work;

    MaxFlow(int N_, int S_, int T_) : N(N_), S(S_), T(T_), adj(N_), level(N_), work(N_) {}

    void addEdge(int u, int v, int cap) {
        adj[u].push_back({v,cap,(int)adj[v].size()});
        adj[v].push_back({u,0,(int)adj[u].size()-1});
    }

    int bfs() {
        fill(level.begin(), level.end(), INF);
        queue<int> q;
        q.push(S);
        level[S] = 0;
        while (!q.empty()) {
            int here = q.front(); q.pop();
            for (int i = 0; i < adj[here].size(); ++i) {
                auto& edge = adj[here][i];
                if (edge.cap > 0 && level[edge.v] == INF) {
                    level[edge.v] = level[here] + 1;
                    q.push(edge.v);
                }
            }
        }
        return level[T] != INF;    
    }

    int dfs(int here, int amount) {
        if (here == T) return amount;
        for (int& i = work[here]; i < adj[here].size(); ++i) {
            auto& edge = adj[here][i];
            if (edge.cap > 0 && level[here] + 1 == level[edge.v]) {
                int cap = dfs(edge.v, min(amount, edge.cap));
                if (cap > 0) {
                    edge.cap -= cap;
                    adj[edge.v][edge.rev].cap += cap;
                    return cap;
                }
            }
        }
        return 0;
    }

    int run() {
        int totalFlow = 0;
        while(bfs()) {
            fill(work.begin(), work.end(), 0);
            while (true) {
                int amount = dfs(S,INF);
                if (!amount) break;
                totalFlow += amount;
            }
        }
        return totalFlow;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M;
    cin >> N >> M;

    int S = N+M, T = S+1;
    MaxFlow maxFlow(N+M+2,S,T);

    for (int i = 0; i < N; ++i) {
        maxFlow.addEdge(S, i, 1);
    }

    for (int i = 0; i < M; ++i) {
        maxFlow.addEdge(N+i, T, 1);
    }

    int count, v;
    for (int i = 0; i < N; ++i) {
        cin >> count;
        for (int j = 0; j < count; ++j) {
            cin >> v;
            maxFlow.addEdge(i,N+v-1,1);
        }
    }

    cout << maxFlow.run() << endl;
}
