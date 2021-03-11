#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> A, vector<int> B) {
    sort(A.begin(), A.end(), greater<int>());
    sort(B.begin(), B.end(), greater<int>());
    
    if (A.back() > B.front()) return 0;
    
    int win = 0, posA = 0, posB = 0;
    while (posA < A.size()) {
        if (A[posA] < B[posB]) {
            ++win; ++posB;
        } 
        ++posA;
    }
    return win;
}
