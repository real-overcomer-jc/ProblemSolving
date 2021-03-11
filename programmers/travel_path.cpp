#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

int N, M;
map<string,int> mapStrToInt;
vector<string> mapIntToStr;
vector<vector<int>> adj;
vector<string> ret;

bool dfs(int here) {
    ret.push_back(mapIntToStr[here]);
    for (int there = 0; there < N; ++there) {
        if (adj[here][there] > 0) {
            --adj[here][there];
            if (dfs(there)) {
                return true;
            } 
            ret.pop_back();
            ++adj[here][there];
        } 
    }
    return ret.size() == M+1;
}

vector<string> solution(vector<vector<string>> tickets) {
    M = tickets.size();
    mapStrToInt.clear();
    for (int i = 0; i < tickets.size(); ++i) {
        for (int j = 0; j < 2; ++j)  
            if (mapStrToInt.count(tickets[i][j]) == 0)
                mapStrToInt[tickets[i][j]] = mapStrToInt.size();
    }
    
    mapIntToStr.clear();
    mapIntToStr = vector<string>(mapStrToInt.size());
    int i = 0;
    for (auto pos = mapStrToInt.begin(); pos != mapStrToInt.end(); ++pos) {
        pos->second = i++;
        mapIntToStr[pos->second] = pos->first;
    }
    
    N = mapStrToInt.size();
    adj = vector<vector<int>>(N, vector<int>(N,0));
    ret.clear();
    for (int i = 0; i < tickets.size(); ++i) {
        int u = mapStrToInt[tickets[i][0]], v = mapStrToInt[tickets[i][1]];
        adj[u][v] += 1;
    }
    
    dfs(mapStrToInt["ICN"]);
    return ret;
}
