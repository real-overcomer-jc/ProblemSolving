#include <string>
#include <vector>

using namespace std;

vector<vector<int>> adj;
vector<bool> visited;

void dfs(int here) {
    visited[here] = true;
    for (int there = 0; there < adj.size(); ++there) {
        if (adj[here][there] && !visited[there]) {
            dfs(there);
        }
    }
}

int dfsAll() {
    visited = vector<bool>(adj.size(),false);
    int count = 0;
    for (int here = 0; here < adj.size(); ++here) {
        if (!visited[here]) {
            dfs(here);
            ++count;
        }
    }
    return count;
}

int solution(int n, vector<vector<int>> computers) {
    adj = computers;
    return dfsAll();
}
