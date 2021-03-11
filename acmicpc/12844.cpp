#include <iostream>
#include <vector>

#define newline '\n'

using namespace std;

struct SegmentTree {
    int n;
    vector<int> tree, lazy;

    SegmentTree(const vector<int>& array) {
        n = array.size();
        tree.resize(4*n);
        lazy.resize(4*n);
        init(array, 1, 0, n-1);
    }

    int init(const vector<int>& array, int node, int nodeLeft, int nodeRight) {
        if (nodeLeft == nodeRight) return tree[node] = array[nodeLeft];
        int mid = nodeLeft + (nodeRight-nodeLeft)/2;
        return tree[node] = init(array, node*2, nodeLeft, mid) ^ init(array, node*2+1, mid+1, nodeRight);
    }

    void update_lazy(int node, int nodeLeft, int nodeRight) {
        if (lazy[node] != 0) {
            tree[node] = (nodeRight-nodeLeft+1)%2 == 1 ? tree[node]^lazy[node] : tree[node];
            if (nodeLeft != nodeRight) {
                lazy[node*2] ^= lazy[node];  
                lazy[node*2+1] ^= lazy[node];
            }
            lazy[node] = 0;
        }
    }

    void update_range(int left, int right, int value, int node, int nodeLeft, int nodeRight) {
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
        tree[node] = tree[node*2] ^ tree[node*2+1];
    }

    void update_range(int left, int right, int value) {
        update_range(left, right, value, 1, 0, n-1);
    }

    int query(int left, int right, int node, int nodeLeft, int nodeRight) {
        update_lazy(node, nodeLeft, nodeRight);
        if (nodeRight < left || right < nodeLeft) return 0;
        if (left <= nodeLeft && nodeRight <= right) return tree[node];

        int mid = nodeLeft + (nodeRight-nodeLeft)/2;
        return query(left, right, node*2, nodeLeft, mid) ^ query(left, right, node*2+1, mid+1, nodeRight);
    }

    int query(int left, int right) {
        return query(left, right, 1, 0, n-1);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int N, M;
    cin >> N;

    vector<int> array(N);
    for (int i = 0; i < N; ++i) {
        cin >> array[i];
    }

    SegmentTree segmentTree(array);
    cin >> M;
    int mode, i, j, k;
    for (int l = 0; l < M; ++l) {
        cin >> mode >> i >> j;
        if (mode == 1) {
            cin >> k;
            segmentTree.update_range(i,j,k);
        } else {
            cout << segmentTree.query(i,j) << newline;
        }
    }
}
