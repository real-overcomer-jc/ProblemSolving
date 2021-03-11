#include <iostream>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <algorithm>

#define newline '\n'

using namespace std;
using ll = long long;
using EventInfo = tuple<ll,ll,ll,ll>; //x, y1, y2, delta

struct SegmentTree {
    vector<ll> ys;
    int n;
    vector<ll> count, sum;

    SegmentTree(const vector<ll>& array) {
        ys = array;
        n = array.size()-1;
        count.resize(4*n);
        sum.resize(4*n);
    }

    void update_range(int left, int right, ll value, int node, int nodeLeft, int nodeRight) {
        if (nodeRight < left || right < nodeLeft) return;
        if (left <= nodeLeft && nodeRight <= right) {
            count[node] += value;
            if (count[node] != 0) {
                sum[node] = ys[nodeRight+1]-ys[nodeLeft];
            } else {
                sum[node] = (nodeLeft != nodeRight) ? sum[node*2]+sum[node*2+1] : 0;
            }
            return;
        }

        int mid = nodeLeft + (nodeRight-nodeLeft)/2;
        update_range(left, right, value, node*2, nodeLeft, mid);
        update_range(left, right, value, node*2+1, mid+1, nodeRight);
        if (count[node] == 0) {
            sum[node] = (nodeLeft != nodeRight) ? sum[node*2]+sum[node*2+1] : 0;
        }
    }

    void update_range(int left, int right, ll value) {
        update_range(left, right, value, 1, 0, n-1);
    }    

    ll query() {
        return sum[1];
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int N;
    cin >> N;

    vector<EventInfo> xEvents;
    vector<ll> ys;
    ll x1, x2, y1, y2; 
    for (int i = 0; i < N; ++i) {
        cin >> x1 >> x2 >> y1 >> y2;
        xEvents.push_back(make_tuple(x1, 1, y1, y2));
        xEvents.push_back(make_tuple(x2, -1, y1, y2));
        ys.push_back(y1);
        ys.push_back(y2);
    }

    sort(xEvents.begin(), xEvents.end());  

    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    unordered_map<ll,ll> y2i;
    for (int i = 0; i < ys.size(); ++i) {
        y2i[ys[i]] = i;
    }

    SegmentTree segmentTree(ys);
    ll prevX = get<0>(xEvents[0]), ret = 0;
    for (auto& xEvent : xEvents) {
        ll x, delta, y1, y2;
        tie(x, delta, y1, y2) = xEvent;
        //cout << "(x-prevX) = " << (x-prevX) << ", segmentTree.query() = " << segmentTree.query() << endl;
        ret += (x-prevX) * segmentTree.query();
        //cout << y2i[y1] << ", " << y2i[y2] << endl;
        segmentTree.update_range(y2i[y1], y2i[y2]-1, delta);
        prevX = x;
    }
    cout << ret << newline;
}  
