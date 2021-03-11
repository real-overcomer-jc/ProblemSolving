#include <string>
#include <vector>
#include <limits>
#include <cstring>

using namespace std;

const int MOD = 1000000007;

int M,N;
vector<vector<int>> board;

int cache[100][100];

bool inRange(int y, int x) {
    return (0 <= y && y < M) && (0 <= x && x < N);
}

int shortest(int y, int x) {
    if (!inRange(y,x) || board[y][x] == 1) return 0;
    if (y == M-1 && x == N-1) return 1;
    
    int& ret = cache[y][x];
    if (ret != -1) return ret;
    return ret = shortest(y+1, x) % MOD + shortest(y, x+1) % MOD;
}

int solution(int m, int n, vector<vector<int>> puddles) {
    M = m, N = n;
    board = vector<vector<int>>(M, vector<int>(N,0));
    for (auto& puddle : puddles) {
        board[puddle[0]-1][puddle[1]-1] = 1;
    }
    
    memset(cache, -1, sizeof(cache));
    return shortest(0,0) % MOD;
}
