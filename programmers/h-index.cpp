#include <vector>
#include <algorithm>

using namespace std;

bool decision(const vector<int>& citations, int h) {
    return h > 0 and citations[h-1] >= h;
}

int parametric_search(const vector<int>& citations, int start, int end) {
    while (start < end) {
        int h = (start+end+1)/2;
        if (decision(citations, h)) {
            start = h;
        } else {
            end = h-1;
        }
    }
    return start;
}

int solution(vector<int> citations) {
    sort(citations.begin(), citations.end(), greater<int>());
    return parametric_search(citations, 0, citations.size());
}
