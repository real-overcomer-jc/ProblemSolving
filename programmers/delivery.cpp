#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using PathInfo = pair<int,int>;

const int INF = 987654321;
vector<vector<pair<int,int>>> adj;

int solution(int N, vector<vector<int> > road, int K) {
    adj.resize(N+1);
    for (auto& edge : road) {
        adj[edge[0]].push_back({edge[1],edge[2]});
        adj[edge[1]].push_back({edge[0],edge[2]});
    }
    
    vector<int> dist(N+1,INF);
    priority_queue<PathInfo, vector<PathInfo>, greater<PathInfo>> pq;
    pq.push({0,1});
    dist[1] = 0;
    while(!pq.empty()) {
        PathInfo pathInfo = pq.top(); pq.pop();
        int here = pathInfo.second;
        int cost = pathInfo.first;
        if (dist[here] < cost) continue;
        
        for (auto& adjInfo : adj[here]) {
            int there = adjInfo.first;
            int weight = adjInfo.second;
            
            if (dist[here] + weight < dist[there]) {
                dist[there] = dist[here] + weight;
                pq.push({dist[there],there});
            }
        }
    }
    
    int ret = 0;
    for (int i = 1; i <= N; ++i) {
        if (dist[i] <= K) ++ret;
    }
    return ret;
}
