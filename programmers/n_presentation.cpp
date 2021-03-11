#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int solution(int N, int number) {
    unordered_set<int> terms[9];
    int nn = 0;
    for (int i = 1; i <= 8; ++i) {
        nn = nn * 10 + N;
        terms[i].insert(nn);
    }
    
    for (int i = 2; i <= 8; ++i) {
        for (int j = 1; j < i; ++j) {
            for (auto& op1 : terms[j]) {
                for (auto& op2 : terms[i-j]) {
                    terms[i].insert(op1+op2);
                    terms[i].insert(op1-op2);
                    terms[i].insert(op1*op2);
                    if (op2) terms[i].insert(op1/op2);
                }
            }
        }
        if (terms[i].count(number) > 0) {
            return i;
        }
    }
    return -1;
}
