#include <string>
#include <vector>

using namespace std;

vector<vector<int>> adj;

int solution(int n, vector<vector<int>> results) {
    adj = vector<vector<int>>(n+1, vector<int>(n+1,0));
    for (auto& edge : results) {
        adj[edge[0]][edge[1]] = 1;
    }
    
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                adj[i][j] = adj[i][j] || (adj[i][k] && adj[k][j]);
    
    int ret = 0;
    for (int i = 1; i <= n; ++i) {
        int count = 0;
        for (int j = 1; j <= n; ++j) {
            if (adj[i][j] || adj[j][i]) ++count;
        }
        if (count == n-1) ++ret;
    }
    return ret;
}
