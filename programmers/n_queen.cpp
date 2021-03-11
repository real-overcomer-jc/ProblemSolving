#include <string>
#include <vector>
#include <cmath>

using namespace std;

int N;
vector<int> col;
int count;

bool promising(int curIdx) {
    for (int rowIdx = 0; rowIdx < curIdx; ++rowIdx) {
        if (col[rowIdx] == col[curIdx] || abs(col[rowIdx] - col[curIdx]) == curIdx - rowIdx)    
            return false;
    }
    return true;
}

void nqueen(int rowIdx) {
    for (int colIdx = 0; colIdx < N; ++colIdx) {
        col[rowIdx] = colIdx;
        if (promising(rowIdx)) {
            if (rowIdx+1 == N) {
                ++count;
            } else {
                nqueen(rowIdx+1);
            }
        }
    }
}

int solution(int n) {
    N = n;
    col = vector<int>(N,-1);
    count = 0;
    nqueen(0);
    return count;
}
