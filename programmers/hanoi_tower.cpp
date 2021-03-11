#include <string>
#include <vector>

using namespace std;

void hanoi(int n, int from, int to, int aux, vector<vector<int>>& moves) {
    if (n == 1) {
        moves.push_back({from,to});
        return;
    }
    
    hanoi(n-1,from,aux,to,moves);
    moves.push_back({from,to});
    hanoi(n-1,aux,to,from,moves);
}

vector<vector<int>> solution(int n) {
    vector<vector<int>> answer;
    hanoi(n,1,3,2,answer);
    return answer;
}
