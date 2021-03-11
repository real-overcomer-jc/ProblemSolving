#include <string>
#include <vector>
#include <queue>

using namespace std;

long long solution(int n, vector<int> works) {
    priority_queue<int> maxHeap(works.begin(), works.end());
    while (n-- > 0 && !maxHeap.empty()) {
        int maxWork = maxHeap.top(); maxHeap.pop();
        if (maxWork > 0) maxHeap.push(maxWork-1);
    }
    
    long long ret = 0;
    while (!maxHeap.empty()) {
        int work = maxHeap.top(); maxHeap.pop();
        ret += work*work;
    }
    return ret;
}
