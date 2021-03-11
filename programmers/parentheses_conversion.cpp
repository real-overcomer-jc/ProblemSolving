#include <string>
#include <vector>
#include <stack>

using namespace std;

const char opening{'('}, closing{')'};

int getBalancedParenLen(string p) {
    stack<char> parenStack;
    parenStack.push(p[0]);
    
    int i = 1;
    while (!parenStack.empty() && i < p.size()) {
        if (parenStack.top() == p[i]) {
            parenStack.push(p[i]);
        } else {
            parenStack.pop();
        }
        ++i;
    }
    return i;
}

bool isCorrectBalancedParen(string p) {
    stack<char> openStack;
    for (int i = 0; i < p.size(); ++i) {
        if (p[i] == opening) {
            openStack.push(opening);
        } else if (p[i] == closing) {
            if (openStack.empty()) return false;
            openStack.pop();
        }
    }
    return openStack.empty();
}

string reverseParen(string p, int i, int j) {
    if (i >= j) return {};
    for (int k = i; k <= j; k++) {
        if (p[k] == opening) 
            p[k] = closing;
        else 
            p[k] = opening;
    }
    return p.substr(i, j-i+1);
}

string solution(string p) {
    if (p.size() == 0) return {};
    
    int len = getBalancedParenLen(p);
    string u = p.substr(0, len);
    string v = p.substr(len);
    
    if (isCorrectBalancedParen(u)) {
        return u + solution(v);
    }
    return "(" + solution(v) + ")" + reverseParen(u, 1, u.size()-2);
}
