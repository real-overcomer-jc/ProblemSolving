#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int dy[] = {1,0,-1,0};
const int dx[] = {0,1,0,-1};

int cache[501][501];

int count(const vector<vector<int>>& board, int y, int x) {
    if (y == board.size()-1 && x == board[0].size()-1) return 1;

    int& ret = cache[y][x];
    if (ret != -1) return ret;

    ret = 0;
    for (int i = 0; i < 4; ++i) {
        int ny = y + dy[i], nx = x + dx[i];
        if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size()) continue;
        if (board[ny][nx] >= board[y][x]) continue;
        ret += count(board, ny, nx);
    }
    return ret;
} 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> board(N, vector<int>(M,0));
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < M; ++x) {
            cin >> board[y][x];
        }
    }

    memset(cache, -1, sizeof cache);
    cout << count(board, 0, 0) << endl;
}
