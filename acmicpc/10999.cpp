#include <iostream>
#include <vector>

#define newline '\n'

using namespace std;
using ll = long long;

struct SegmentTree {
    int n;
    vector<ll> tree, lazy;
    
    SegmentTree(const vector<ll>& array) {
        n = array.size();
        tree.resize(4*n);
        lazy.resize(4*n);
        init(array, 1, 0, n-1);
    }

    ll init(const vector<ll>& array, int node, int left, int right) {
        if (left == right) return tree[node] = array[left];
        int mid = left + (right-left)/2;
        return tree[node] = init(array, node*2, left, mid) + init(array, node*2+1, mid+1, right);
    }

    void update_lazy(int node, int nodeLeft, int nodeRight) {
        if (lazy[node] != 0) {
            tree[node] += (nodeRight-nodeLeft+1) * lazy[node];
            if (nodeLeft != nodeRight) { //단말 노드 일 때 
                lazy[node*2] += lazy[node];
                lazy[node*2+1] += lazy[node];
            }
            lazy[node] = 0;
        }
    } 

    void update_range(int left, int right, ll value, int node, int nodeLeft, int nodeRight) {
        update_lazy(node, nodeLeft, nodeRight);
        if (nodeRight < left || right < nodeLeft) return;
        if (left <= nodeLeft && nodeRight <= right) {
            lazy[node] = value;
            update_lazy(node, nodeLeft, nodeRight);
            return;
        }

        int mid = nodeLeft + (nodeRight-nodeLeft)/2;
        update_range(left, right, value, node*2, nodeLeft, mid);
        update_range(left, right, value, node*2+1, mid+1, nodeRight);
        tree[node] = tree[node*2] + tree[node*2+1];
    }

    void update_range(int left, int right, ll value) {
        update_range(left, right, value, 1, 0, n-1);
    }

    ll query(int left, int right, int node, int nodeLeft, int nodeRight) {
        update_lazy(node, nodeLeft, nodeRight);
        if (nodeRight < left || right < nodeLeft) return 0;
        if (left <= nodeLeft && nodeRight <= right) return tree[node];

        int mid = nodeLeft + (nodeRight-nodeLeft)/2;
        return query(left, right, node*2, nodeLeft, mid) + query(left, right, node*2+1, mid+1, nodeRight);
    }

    ll query(int left, int right) {
        return query(left, right, 1, 0, n-1);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    vector<ll> array(N);
    for (int i = 0; i < N; ++i) {
        cin >> array[i];
    }

    SegmentTree segmentTree(array);
    int mode, i, j, k;
    for (int l = 0; l < M+K; ++l) {
        cin >> mode;
        if (mode == 1) {
            cin >> i >> j >> k;
            segmentTree.update_range(i-1, j-1, k);
        } else {
            cin >> i >> j;
            cout << segmentTree.query(i-1, j-1) << newline;
        }
    }
}
