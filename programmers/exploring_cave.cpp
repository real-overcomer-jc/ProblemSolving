#include <string>
#include <vector>
#include <set>

using namespace std;

vector<set<int>> adj;
vector<bool> visited, finished;

bool hasCycle;

void makeDAG(int here) {
    visited[here] = true;
    for (int there : adj[here]) {
        if (!visited[there]) {
            adj[there].erase(here);
            makeDAG(there);
        } 
    }
}

void detectCycle(int here) {
    visited[here] = true;
    for (int there : adj[here]) {
        if (!visited[there]) {
            detectCycle(there);
        } else if (!finished[there]) {
            hasCycle = true;
        }
    }
    finished[here] = true;
}

bool solution(int n, vector<vector<int>> path, vector<vector<int>> order) {
    adj.resize(n);
    for (auto& edge : path) {
        adj[edge[0]].insert(edge[1]);
        adj[edge[1]].insert(edge[0]);
    }
    
    visited = vector<bool>(n,false);
    makeDAG(0);
    
    for (auto& edge : order) {
        adj[edge[0]].insert(edge[1]);
    }
    
    hasCycle = false;
    visited = finished = vector<bool>(n,false);
    detectCycle(0);
    return !hasCycle;
}
