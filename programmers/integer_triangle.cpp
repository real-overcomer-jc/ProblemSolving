#include <string>
#include <vector>
#include <cstring>

using namespace std;

int cache[500][500];

bool inRange(const vector<vector<int>>& triangle, int y, int x) {
    return y < triangle.size();
}

int move(const vector<vector<int>>& triangle, int y, int x) {
    if (y+1 == triangle.size()) return triangle[y][x];
    int& ret = cache[y][x];
    if (ret != -1) return ret;
    return ret = triangle[y][x] + max(move(triangle,y+1,x), move(triangle,y+1,x+1));
}

int solution(vector<vector<int>> triangle) {
    memset(cache, -1, sizeof(cache));
    return move(triangle, 0, 0);
}
