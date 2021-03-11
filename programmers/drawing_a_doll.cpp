#include <string>
#include <vector>
#include <stack>
#include <iostream>

using namespace std;

int solution(vector<vector<int>> board, vector<int> moves) {
    int answer = 0;
    stack<int> dollStack;
    for (int i = 0; i < moves.size(); ++i) {
        int x = moves[i]-1, y = 0;
        for (; y < board.size(); ++y) {
            if (board[y][x] != 0) break;
        }
        if (y == board.size()) continue;
        
        int doll = board[y][x];
        if (!dollStack.empty() && dollStack.top() == doll) {
            dollStack.pop();
            answer += 2;
        } else {
            dollStack.push(doll);
        }
        board[y][x] = 0;
    }
    return answer;
}
