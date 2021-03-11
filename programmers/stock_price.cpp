#include <string>
#include <vector>
#include <stack>

using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> ret(prices.size());
    stack<int> s;
    for (int i = 0; i < prices.size(); ++i) {
        while (!s.empty() && prices[s.top()] > prices[i]) {
            int j = s.top(); s.pop();
            ret[j] = (i == prices.size()) ? i-j-1 : i-j;
        }
        s.push(i);
    }
    
    while(!s.empty()) {
        int j = s.top(); s.pop();
        ret[j] = prices.size()-j-1;
    }
    return ret;
}
