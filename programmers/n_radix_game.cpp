#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> parseNumbers(int n, int i) {
    if (i == 0) return {0};
    
    vector<int> ret;
    while (i > 0) {
        ret.push_back(i % n);
        i = i / n;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

string solution(int n, int t, int m, int p) {
    vector<int> sequence;
    int i = 0;
    while (sequence.size() < p + m*(t-1)) {
        vector<int> digits = parseNumbers(n,i);
        sequence.insert(sequence.end(), digits.begin(), digits.end());
        ++i;
    }
    
    string ret;
    for (int i = 0; i < t; ++i) {
        int number = sequence[(p-1)+m*i];
        if (number < 10) ret.push_back(number + '0');
        else ret.push_back(number - 10 + 'A');
    }
    return ret;
}
