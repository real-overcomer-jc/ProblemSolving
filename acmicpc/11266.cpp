#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
vector<int> discovered, cutVertexes;
int counter;

int findCutVertex(int here, bool isRoot) {
    int ret = (discovered[here] = counter++);
    int components = 0, subtrees = 0;
    for (auto& there : adj[here]) {
        if (discovered[there] == -1) {
            ++subtrees;
            int ancestor = findCutVertex(there, false);
            if (!isRoot && discovered[here] <= ancestor) {
                ++components;
            }
            ret = min(ret, ancestor);
        } else {
            ret = min(ret, discovered[there]);
        }
    }
    if ((isRoot && subtrees > 1) || components > 0) cutVertexes.push_back(here);
    return ret;
}

int main() {
    int N, M;
    cin >> N >> M;

    adj = vector<vector<int>>(N+1);
    int u, v;
    for (int i = 0; i < M; ++i) {
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    counter = 0;
    discovered = vector<int>(N+1,-1);
    for (int i = 1; i <= N; ++i) {
        if (discovered[i] == -1) findCutVertex(i, true);
    }

    cout << cutVertexes.size() << endl;
    sort(cutVertexes.begin(), cutVertexes.end());
    for (int cutVertex : cutVertexes) {
        cout << cutVertex << " ";
    }
    cout << endl;
}
