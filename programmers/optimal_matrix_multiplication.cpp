#include <string>
#include <vector>
#include <cstring>
#include <limits>

using namespace std;

int cache[200][200];

int minMulCount(const vector<vector<int>>& matrix_sizes, int i, int j) {
    if (i == j) return 0;
    if (i+1 == j) return matrix_sizes[i][0] * matrix_sizes[i][1] * matrix_sizes[j][1];
    
    int& ret = cache[i][j];
    if (ret != -1) return ret;
    
    ret = numeric_limits<int>::max();
    for (int k = i; k < j; ++k) {
        int count = minMulCount(matrix_sizes, i, k) + minMulCount(matrix_sizes, k+1, j);
        count += matrix_sizes[i][0] * matrix_sizes[k][1] * matrix_sizes[j][1]; 
        ret = min(ret, count);
    }
    return ret;
}

int solution(vector<vector<int>> matrix_sizes) {
    memset(cache, -1, sizeof cache);
    return minMulCount(matrix_sizes, 0, matrix_sizes.size()-1);
}
