#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(vector<int> numbers) {
    vector<string> strNumbers(numbers.size());
    for (int i = 0; i < numbers.size(); ++i) {
        strNumbers[i] = to_string(numbers[i]);
    }
    
    auto criterion = [](const string& lhs, const string& rhs) {
        return lhs+rhs > rhs+lhs;
    };
    sort(strNumbers.begin(), strNumbers.end(), criterion);
    
    string ret;
    for (auto& s : strNumbers) {
        ret += s;
    }
    if (all_of(ret.begin(), ret.end(), [](char c){return c == '0';})) 
        return "0";
    return ret;
}
