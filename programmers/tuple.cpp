#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

vector<vector<int>> getCollections(const string& s) {
    vector<vector<int>> ret;
    auto begin = s.find_first_not_of("{},");
    auto end = string::npos;
    while (begin != string::npos) {
        vector<int> set;
        while (true) {
            end = s.find_first_of("{},", begin);
            int number = stoi(s.substr(begin,end-begin));
            set.push_back(number);
            if (s[end] == '}') break;
            begin = s.find_first_not_of("{},",end);
        }
        ret.push_back(set);
        begin = s.find_first_not_of("{},",end);
    }
    return ret;
} 

vector<int> solution(string s) {
    vector<vector<int>> splited = getCollections(s);
    auto criterion = [] (const vector<int>& lhs, const vector<int>& rhs) {
        return lhs.size() < rhs.size();
    };
    sort(splited.begin(), splited.end(), criterion);
    
    vector<int> tuple;
    map<int,bool> tupleMap;
    for (int i = 0; i < splited.size(); ++i) {
        for (int j = 0; j < i+1; ++j) {
            if (!tupleMap[splited[i][j]]) {
                tuple.push_back(splited[i][j]);
                tupleMap[splited[i][j]] = true;
            }
        }
    }
    return tuple;
}
