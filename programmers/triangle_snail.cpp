#include <vector>

using namespace std;

const int dy[] = {1,0,-1};
const int dx[] = {0,1,-1};

vector<int> solution(int n) {
    vector<vector<int>> triangle(n, vector<int>(n,0));
    int total = (n * (n+1)) / 2, dir = 0, y = 0, x = 0;
    for (int i = 1; i <= total; ++i) {
        triangle[y][x] = i;
        if (y+dy[dir] == n || x+dx[dir] == n || triangle[y+dy[dir]][x+dx[dir]] != 0) dir = (dir+1) % 3;
        y = y+dy[dir], x = x+dx[dir];
    }

    vector<int> ret;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            ret.push_back(triangle[i][j]);
        }
    }
    return ret;
}
