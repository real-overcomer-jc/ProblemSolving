#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> routes) {
    auto criterion = [] (vector<int>& a, vector<int>& b){
            return a[1] < b[1];
    };
    sort(routes.begin(), routes.end(), criterion);
    
    int installed = 0, end = -30001;
    for (auto& range : routes) {
        if (end < range[0]) {
            ++installed;
            end = range[1];
        }
    }
    return installed;
}
