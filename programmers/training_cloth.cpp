#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
    unordered_map<int,bool> canBorrowMap;
    for (const int& no : reserve) {
        canBorrowMap[no] = true;
    }
    
    vector<bool> processed(n+1,false);
    n -= lost.size();
    for (const int& no : lost) {
        if (canBorrowMap[no]) {
            canBorrowMap[no] = false;
            processed[no] = true;
            ++n;
        }
    }
    
    for (const int& no : lost) {
        if (processed[no]) continue;
        if (no > 1 && canBorrowMap[no-1]) {
            canBorrowMap[no-1] = false;
            ++n;
        } else if (canBorrowMap[no+1]) {
            canBorrowMap[no+1] = false;
            ++n;
        }
    }
    return n;
}
