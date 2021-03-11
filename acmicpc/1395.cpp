#include <iostream>
#include <vector>

#define newline '\n'

using namespace std;
using ll = int;

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
            tree[node] = (nodeRight-nodeLeft+1) - tree[node];
            if (nodeLeft != nodeRight) {
                lazy[node*2] ^= 1;
                lazy[node*2+1] ^= 1;
            }
            lazy[node] = 0;
        }
    }

    void update_range(int left, int right, int node, int nodeLeft, int nodeRight) {
        update_lazy(node, nodeLeft, nodeRight);
        if (nodeRight < left || right < nodeLeft) return;
        if (left <= nodeLeft && nodeRight <= right) {
            lazy[node] ^= 1;
            update_lazy(node, nodeLeft, nodeRight);
            return;
        }

        int mid = nodeLeft + (nodeRight-nodeLeft)/2;
        update_range(left, right, node*2, nodeLeft, mid);
        update_range(left, right, node*2+1, mid+1, nodeRight);
        tree[node] = tree[node*2] + tree[node*2+1];
    }

    void update_range(int left, int right) {
        update_range(left, right, 1, 0, n-1);
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

    int N, M;
    cin >> N >> M;

    vector<ll> array(N,0);
    SegmentTree segmentTree(array);
    int mode, i, j;
    for (int k = 0; k < M; ++k) {
        cin >> mode >> i >> j;
        if (mode == 0) {
            segmentTree.update_range(i-1, j-1);
        } else {
            cout << segmentTree.query(i-1, j-1) << newline;
        }
    }
}
