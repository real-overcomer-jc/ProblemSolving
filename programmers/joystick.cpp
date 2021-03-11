#include <string>
#include <vector>

using namespace std;

int solution(string name) {
    int vertialMoves = 0;
    for (char ch : name) {
        if (ch == 'A') continue;
        vertialMoves += min(ch-'A', 'Z'-ch+1);
    }
    
    const int len = name.size();
    int horizontalMoves = len-1;
    for (int i = 0; i < len; ++i) {
        if (name[i] == 'A') continue;
        int next = i+1;
        while (next < len && name[next] == 'A') ++next;
        if (next == len) break;
        horizontalMoves = min(horizontalMoves, min(2*i+len-next, 2*(len-next)+i));
    }
    return vertialMoves + horizontalMoves;
}
