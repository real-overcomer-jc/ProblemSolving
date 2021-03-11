#include <iostream>
#include <vector>
#include <stack>

#define newline '\n'

using namespace std;

long long maxRectangleArea(vector<long long>& h) {
    h.push_back(0);
    long long ret = 0;
    stack<int> s;
    for (int i = 0; i < h.size(); ++i) {
        while (!s.empty() && h[s.top()] >= h[i]) {
            long long height = h[s.top()]; s.pop();
            int l = s.empty() ? -1 : s.top(); 
            int r = i;
            ret = max<long long>(ret, (r-l-1)*height);
        }
        s.push(i);
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    while(true) {
        int N;
        cin >> N;
        if (N == 0) break;

        vector<long long> h(N);
        for (int i = 0; i < N; ++i) {
            cin >> h[i];
        }
        cout << maxRectangleArea(h) << newline;
    }
}
