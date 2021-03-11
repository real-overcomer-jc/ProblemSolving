#include <vector>
#include <queue>
#include <cstring>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = 987654321;

int cache[101][101];

//vector<int> adj1[101], adj2[101];
vector<vector<int>> adj1, adj2;

struct MCMF {
    int N, S, T;
    vector<vector<int>> adj, cost, capacity, flow;
    
    MCMF(int N_, int S_, int T_) : N(N_), S(S_), T(T_), 
    adj(N_), cost(N_,vector<int>(N_,0)),
    capacity(N_,vector<int>(N_,0)), flow(N_,vector<int>(N_,0))
    {}
    
    void addEdge(int u, int v, int c, int d) {
        adj[u].push_back(v);
        adj[v].push_back(u);
        capacity[u][v] = c;
        cost[u][v] = d;
        cost[v][u] = -d;
    }
    
    int run() {
        int minCost = 0;
        int dist[N], prev[N], inQ[N];
        while (true) {
            fill(dist, dist+N, INF);
            fill(prev, prev+N, -1);
            fill(inQ, inQ+N, 0);
            
            queue<int> q;
            q.push(S);
            dist[S] = 0;
            //prev[S] = S;
            //inQ[S] = true;
            
            while (!q.empty()) {
                int here = q.front(); q.pop();
                inQ[here] = 0;
                
                for (int there : adj[here]) {
                    if (capacity[here][there] - flow[here][there] > 0) {
                        if (dist[here] + cost[here][there] < dist[there]) {
                            dist[there] = dist[here] + cost[here][there];
                            prev[there] = here;
                            if (!inQ[there]) {
                                q.push(there);
                                inQ[there] = 1;
                            }
                        }
                    }
                }
            }
            
            if (prev[T] == -1) break;
            
            /*int minFlow = INF, totalCost = 0;
            for (int i = T; i != S; i = prev[i]) {
                minFlow = min(minFlow, capacity[prev[i]][i] - flow[prev[i]][i]);
                totalCost += cost[prev[i]][i];
            }*/
            
            for (int i = T; i != S; i = prev[i]) {
                ++flow[prev[i]][i];
                --flow[i][prev[i]];
                minCost += cost[prev[i]][i];
            }
            
            //maxFlow += minFlow;
            //minCost += totalCost * minFlow;
        }     
        return minCost;
    }
};

int getCommonPartSize(int p1, int pp1, int p2, int pp2) {
    if (adj1[p1].size() == 1 && adj2[p2].size() == 1) return 1;
    
    int& ret = cache[p1][p2];
    if (ret != -1) return ret;
    
    int N = adj1[p1].size(), M = adj2[p2].size();
    int S = N+M, T = S+1;
    MCMF mcmf(N+M+2, S, T);
    for (int i = 0; i < N; ++i) {
        int c1 = adj1[p1][i];
        if (c1 == pp1) continue;
        for (int j = 0; j < M; ++j) {
            int c2 = adj2[p2][j];
            if (c2 == pp2) continue;
            int cost = getCommonPartSize(c1, p1, c2, p2);
            mcmf.addEdge(i, N+j, 1, -cost);
        }
        mcmf.addEdge(S, i, 1, 0);
    }
    
    for (int i = 0; i < M; ++i) {
        mcmf.addEdge(N+i, T, 1, 0);
    }
    
    return ret = -mcmf.run() + 1;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n1, vector<vector<int>> g1, int n2, vector<vector<int>> g2) {
    memset(cache, -1, sizeof cache);
    //for (int i = 0; i < 101; i++) adj1[i].clear(), adj2[i].clear();
    adj1.clear(); adj2.clear();
    adj1.resize(101); adj2.resize(101);
    
    for (auto& edge : g1) {
        int u = edge[0], v = edge[1];
        adj1[u].push_back(v);
        adj1[v].push_back(u);
    }
    
    for (auto& edge : g2) {
        int u = edge[0], v = edge[1];
        adj2[u].push_back(v);
        adj2[v].push_back(u);
    }
    
    return getCommonPartSize(1,0,1,0);
}
