#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int power(int x, int n) {
    int ret = 1;
    for (int i = 0; i < n; ++i) {
        ret *= x;
    }
    return ret;
}

int solution(string dartResult) {
    vector<int> terms;
    for (int i = 0; i < dartResult.size(); ++i) {
        if (isdigit(dartResult[i])) {
            if (i+1 < dartResult.size() && isdigit(dartResult[i+1])) {
                terms.push_back(stoi(dartResult.substr(i,2)));
                ++i;
            } else {
                terms.push_back(stoi(dartResult.substr(i,1)));
            }
        } else {
            if (dartResult[i] == 'S') {
                terms.back() = power(terms.back(),1);
            } else if (dartResult[i] == 'D') {
                terms.back() = power(terms.back(),2);
            }  else if (dartResult[i] == 'T') {
                terms.back() = power(terms.back(),3);
            }  else if (dartResult[i] == '*') {
                terms.back() = terms.back() * 2;
                if (terms.size() > 1) 
                    terms[terms.size()-2] = terms[terms.size()-2] * 2;
            }  else if (dartResult[i] == '#') {
                terms.back() = terms.back() * -1;
            }  
        }
    }
    return accumulate(terms.begin(), terms.end(), 0);
}
