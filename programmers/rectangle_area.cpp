#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <tuple>

using namespace std;
using Event = tuple<int,int,int,int>;

struct SegmentTree {
    vector<int> ys;
    int n;
    vector<int> count, sum;
    
    SegmentTree(const vector<int>& array) {
        ys = array;
        n = array.size()-1;
        count.resize(4*n);
        sum.resize(4*n);
    }
    
    void update_range(int left, int right, int value, int node, int nodeLeft, int nodeRight) {
        if (nodeRight < left || right < nodeLeft) return;
        if (left <= nodeLeft && nodeRight <= right) {
            count[node] += value;
            if (count[node] != 0) {
                sum[node] = ys[nodeRight+1] - ys[nodeLeft];
            } else {
                sum[node] = (nodeLeft != nodeRight) ? sum[node*2] + sum[node*2+1] : 0;
            }
            return;
        }
        
        int mid = nodeLeft + (nodeRight-nodeLeft)/2;
        update_range(left, right, value, node*2, nodeLeft, mid);
        update_range(left, right, value, node*2+1, mid+1, nodeRight);
        if (count[node] == 0) {
            sum[node] = (nodeLeft != nodeRight) ? sum[node*2] + sum[node*2+1] : 0;
        }
    }
    
    void update_range(int left, int right, int value) {
        update_range(left, right, value, 1, 0, n-1);
    }
    
    int query() {
        return sum[1];
    }
};

long long solution(vector<vector<int>> rectangles) {
    vector<Event> xEvents;
    vector<int> y;
    for (auto& rect : rectangles) {
        xEvents.push_back(make_tuple(rect[0], 1, rect[1], rect[3]));
        xEvents.push_back(make_tuple(rect[2], -1, rect[1], rect[3]));
        y.push_back(rect[1]);
        y.push_back(rect[3]);
    }
    sort(xEvents.begin(), xEvents.end());
    sort(y.begin(), y.end());
    y.erase(unique(y.begin(), y.end()), y.end());

    unordered_map<int,int> yRefId;
    for (int i = 0; i < y.size(); ++i) {
        yRefId[y[i]] = i;
    }
    
    long long totalArea = 0, prevX = 0;
    SegmentTree segmentTree(y);
    for (auto& event : xEvents) {
        int x, delta, y1, y2;
        tie(x, delta, y1, y2) = event;
        totalArea += (x-prevX) * segmentTree.query();
        segmentTree.update_range(yRefId[y1], yRefId[y2]-1, delta); 
        prevX = x;
    }
    return totalArea;
}
