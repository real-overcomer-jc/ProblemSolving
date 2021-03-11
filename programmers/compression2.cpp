#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> solution(string msg) {
    map<string,int> dictionary;
    for (int i = 0; i < 26; ++i) {
        dictionary[string(1,'A'+i)] = i+1;
    }
    
    vector<int> ret;
    for (int i = 0; i < msg.size(); ++i) {
        string token(1,msg[i]);
        while (i+1 < msg.size()) {
            token.push_back(msg[i+1]);
            if (dictionary.count(token) == 0) {
                dictionary[token] = dictionary.size() + 1;
                token.pop_back();
                break;
            } 
            ++i;
        }
        ret.push_back(dictionary[token]);
    }
    return ret;
}
