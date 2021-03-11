#include <iostream>
#include <string>

using namespace std;

int expand(const string& s, int left, int right) {
    while (left >= 0 && right < s.size() && s[left] == s[right]) {
        --left; ++right;
    }
    return right-left-1;
}

int solution(string s)
{
    int start = 0, end = 0;
    for (int i = 0; i < s.size(); ++i) {
        int len = max(expand(s,i,i), expand(s,i,i+1));
        if (end-start+1 < len) {
            start = i-(len-1)/2;
            end = i+len/2;
        }
    }
    return end-start+1;
}
