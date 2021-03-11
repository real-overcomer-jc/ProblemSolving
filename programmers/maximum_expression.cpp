#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <cmath>
#include <iostream>

using namespace std;
using int64 = int;

int64 best;

vector<string> split(const string& s) {
    vector<string> ret;
    auto begin = s.find_first_not_of(" ");
    auto end = string::npos;
    while (begin != string::npos) {
        end = s.find_first_of(" ",begin);
        if (end == string::npos) end = s.size();
        ret.push_back(s.substr(begin,end-begin));
        begin = s.find_first_not_of(" ",end);
    }
    return ret;
}

string toPosfixExpr(const string& infix, const vector<char>& ordered) {
    map<char,int> orderedMap;
    for (int i = 0; i < ordered.size(); ++i) {
        orderedMap[ordered[i]] = i;
    }
    
    string postfixExpr;
    stack<char> operatorStack;
    for (int i = 0; i < infix.size(); ++i) {
        if (isdigit(infix[i])) {
            postfixExpr.push_back(infix[i]);
        } else {
            postfixExpr.push_back(' ');
            while(!operatorStack.empty() && orderedMap[operatorStack.top()] <= orderedMap[infix[i]]) {
                postfixExpr.push_back(operatorStack.top());
                postfixExpr.push_back(' ');
                operatorStack.pop();
            }        
            operatorStack.push(infix[i]);
            postfixExpr.push_back(' ');
        }
    }
    
    while (!operatorStack.empty()) {
        postfixExpr.push_back(' ');
        postfixExpr.push_back(operatorStack.top());
        operatorStack.pop();
    }
    return postfixExpr;
}

int64 evaluate(const string& infix, const vector<char>& ordered) {
    string postfixExpr = toPosfixExpr(infix, ordered);
    //cout << "postfix = " << postfixExpr << endl;
    
    stack<int64> evalStack;
    vector<string> tokens = split(postfixExpr);
    for (auto& token : tokens) {
        //cout << "token : " << token << endl;
        if (isdigit(token[0])) {
            evalStack.push(stoi(token));
        } else {
            int64 op2 = evalStack.top(); evalStack.pop();
            int64 op1 = evalStack.top(); evalStack.pop();
            if (token == "+") {
                evalStack.push(op1+op2);
            } else if (token == "-") {
                evalStack.push(op1-op2);
            } else {
                evalStack.push(op1*op2);
            }
        }
    }
    return evalStack.top();
}

void permutate(const vector<char>& operators, const string& expression, int used, vector<char>& ordered) {
    if (operators.size() == ordered.size()) {
        best = max(best, abs(evaluate(expression, ordered)));
        return;
    }
    for (int i = 0; i < operators.size(); ++i) {
        if (used & (1<<i)) continue;
        ordered.push_back(operators[i]);
        permutate(operators, expression, used | (1<<i), ordered);
        ordered.pop_back();
    }
}

long long solution(string expression) {
    set<char> operatorSet;
    for (int i = 0; i < expression.size(); ++i) {
        if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*')
        operatorSet.insert(expression[i]);
    }
    
    best = 0;
    vector<char> operators(operatorSet.begin(), operatorSet.end()), ordered;
    permutate(operators, expression, 0, ordered);
    return best;
}
