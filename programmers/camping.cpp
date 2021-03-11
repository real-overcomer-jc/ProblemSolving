#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int n, vector<vector<int>> data) {
    vector<vector<int>> rangeSum(n,vector<int>(n,0));
    set<int> xPoints, yPoints;
    for (int i = 0; i < n; ++i) {
        xPoints.insert(data[i][0]);
        yPoints.insert(data[i][1]);
    }
    
    for (int i = 0; i < n; ++i) {
        data[i][0] = distance(xPoints.begin(), xPoints.find(data[i][0]));
        data[i][1] = distance(yPoints.begin(), yPoints.find(data[i][1]));
        rangeSum[data[i][0]][data[i][1]] = 1;
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i > 0) rangeSum[i][j] += rangeSum[i-1][j];
            if (j > 0) rangeSum[i][j] += rangeSum[i][j-1];
            if (i > 0 && j > 0) rangeSum[i][j] -= rangeSum[i-1][j-1];
        }
    }
    
    int ret = 0;
    for (int i = 0; i < n; ++i) {
        int x1 = data[i][0], y1 = data[i][1];
        for (int j = i+1; j < n; ++j) {
            int x2 = data[j][0], y2 = data[j][1];
            if (x1 == x2 || y1 == y2) continue;
            
            int startX = min(x1,x2), endX = max(x1,x2), startY = min(y1,y2), endY = max(y1,y2);
            int count = rangeSum[endX-1][endY-1] - rangeSum[startX][endY-1] - rangeSum[endX-1][startY] + rangeSum[startX][startY];
            if (count == 0) ++ret;
        }
    }
    return ret;
}
