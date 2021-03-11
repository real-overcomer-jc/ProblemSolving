#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(string number, int k) {
    string ret;
    int startIdx = 0;
    for (int i = 0; i < number.size()-k; ++i) {
        auto it = max_element(number.begin()+startIdx, number.begin()+k+i+1);
        ret.push_back(*it);
        startIdx = distance(number.begin(),it) + 1;
    }
    return ret;
}
