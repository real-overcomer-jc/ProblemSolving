nclude <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX = 1e5+1;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int N, K;
    cin >> N >> K;
    
    if (N == K) {
        cout << 0 << '\n';   
        return 0;
    }

    vector<int> dist(MAX, -1);
    queue<int> q;
    q.push(N);
    dist[N] = 0;
    while (!q.empty()) {
        int here = q.front(); q.pop();

        vector<int> nextStates;
        nextStates.push_back(here*2);
        nextStates.push_back(here+1);
        nextStates.push_back(here-1);

        for (int next : nextStates) {
            if (next == K) {
                cout << dist[here] + 1 << '\n';
                return 0;
            } 

            if (0 < next && next < MAX && dist[next] == -1) {
                dist[next] = dist[here] + 1;
                q.push(next);
            }
        }    
    }
    cout << "error" << '\n';
}
