#include <string>
#include <cstring>
#include <vector>
#include <regex>
#include <algorithm>

using namespace std;

const regex headPattern(R"(^[a-zA-Z ,-]+)");
const regex numberPattern(R"([0-9]{1,5})");

void toLowerCase(string& s) {
    transform(s.cbegin(), s.cend(), s.begin(), [](char c) { return tolower(c);});
}

vector<string> tokenize(const string& a) {
    smatch m;
    regex_search(a.begin(), a.end(), m, headPattern);
    string aHead = m.str();
    toLowerCase(aHead);

    regex_search(m.suffix().first, a.end(), m, numberPattern);
    string aNumber = m.str();

    /*regex tailPattern(R"([0-9a-zA-Z ,-]*?$)");
    regex_search(a.begin() + aHead.size() + aNumber.size(), a.end(), m, tailPattern);
    string aTail = m.str();*/
    return {aHead, aNumber};
}

vector<string> solution(vector<string> files) {
    auto criterion = [] (const pair<string,int>& a, const pair<string,int>& b) {
        vector<string> aTokens = tokenize(a.first);
        vector<string> bTokens = tokenize(b.first);
        if (aTokens[0] < bTokens[0]) 
            return true;
        else if (aTokens[0] == bTokens[0] && stoi(aTokens[1]) < stoi(bTokens[1]))
            return true;
        else if (aTokens[0] == bTokens[0] && stoi(aTokens[1]) == stoi(bTokens[1]))              return a.second < b.second;
        return false;
    };

    vector<pair<string,int>> ordered;
    for (int i = 0; i < files.size(); ++i) {
        ordered.push_back({files[i],i});
    }
    sort(ordered.begin(), ordered.end(), criterion);

    vector<string> ret;
    for (int i = 0; i < ordered.size(); ++i) {
        ret.push_back(ordered[i].first);
    }
    return ret;
}
