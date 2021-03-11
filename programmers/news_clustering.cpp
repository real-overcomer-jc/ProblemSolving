#include <string>
#include <map>
#include <algorithm>

using namespace std;

int solution(string str1, string str2) {
    auto lambda = [](char ch) { return tolower(ch); };
    transform(str1.begin(), str1.end(), str1.begin(), lambda);
    transform(str2.begin(), str2.end(), str2.begin(), lambda);
    
    map<string,int> freq1;
    for (int i = 0; i+1 < str1.size(); ++i) {
        if (isalpha(str1[i]) && isalpha(str1[i+1])) {
            string token = str1.substr(i,2);
            ++freq1[token];
        }
    }
    
    map<string,int> freq2;
    for (int i = 0; i+1 < str2.size(); ++i) {
        if (isalpha(str2[i]) && isalpha(str2[i+1])) {
            string token = str2.substr(i,2);
            ++freq2[token];
        }
    }

    int intersectCnt = 0;
    int unionCnt = 0;
    for (auto pos = freq1.begin(); pos != freq1.end(); ++pos) {
        if (freq2.count(pos->first) > 0) {
            intersectCnt += min(freq2[pos->first], pos->second);
            unionCnt += max(freq2[pos->first], pos->second);
        } else {
            unionCnt += pos->second;
        }
    }
    
    for (auto pos = freq2.begin(); pos != freq2.end(); ++pos) {
        if (freq1.count(pos->first) == 0) {
            unionCnt += pos->second;
        } 
    }
    
    if (intersectCnt == 0 && unionCnt == 0) return 65536;
    else if (unionCnt == 0) return 0;
    double ret = (intersectCnt * 65536) / static_cast<double>(unionCnt);
    return static_cast<int>(ret);
}
