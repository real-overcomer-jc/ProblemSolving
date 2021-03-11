#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<string,pair<int,vector<int>>> genresMap;

vector<int> solution(vector<string> genres, vector<int> plays) {
    for (int i = 0; i < genres.size(); ++i) {
        if (genresMap.count(genres[i]) == 0) {
            genresMap[genres[i]] = {plays[i],{i}};
        } else {
            genresMap[genres[i]].first += plays[i];
            genresMap[genres[i]].second.push_back(i);
        }
    }
    
    vector<pair<int,vector<int>>> ordered;
    for (auto& entry : genresMap) {
        ordered.push_back(entry.second);
    }
    
    auto criterion1 = [&](const pair<int,vector<int>>& lhs, const pair<int,vector<int>>& rhs) {
      return lhs.first > rhs.first;  
    };
    sort(ordered.begin(), ordered.end(), criterion1);
    
    vector<int> ret;
    auto criterion2 = [&](int i, int j) {
      return plays[i] > plays[j];  
    };
    for (auto& elem : ordered) {
        vector<int>& rank = elem.second;
        sort(rank.begin(), rank.end(), criterion2);
        int size = (rank.size() > 1) ? 2 : 1; 
        ret.insert(ret.end(), rank.begin(), rank.begin()+size);
    }
    return ret;
}
