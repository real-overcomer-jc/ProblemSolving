#include <vector>
#include <cstring>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = 987654321;

int cache[1<<8][1<<15];

int countMinRequired(int n, int m, int picked, int visited, const vector<int>& week, const vector<int>& dist) {
    if (visited == (1<<week.size())-1) {
        return 0;
    } else if (m == dist.size()) {
        return INF;
    }

    int& ret = cache[picked][visited];
    if (ret != -1) return ret;
    ret = INF;

    for (int start = 0; start < week.size(); ++start) {
        if (visited & (1<<start)) continue;
        int newVisited = visited | (1<<start);

        for (int person = 0; person < dist.size(); ++person) {
            if (picked & (1<<person)) continue;
            int newPicked = picked | (1<<person);

            vector<int> occupied;
            int startLoc = week[start];
            int endLoc = startLoc + dist[person];
            for (int i = 0; i < week.size(); ++i) {
                if (newVisited & (1<<i)) continue;
                int nextLoc = week[i];
                if (endLoc > n-1 && nextLoc < startLoc) {
                    endLoc = endLoc % n + n;
                    nextLoc += n;
                }
                if (startLoc < nextLoc && nextLoc <= endLoc) newVisited |= (1<<i);
                occupied.push_back(i);
            }

            ret = min(ret, 1 + countMinRequired(n, m+1, newPicked, newVisited, week, dist));
        }
    }    
    return ret;
}

int solution(int n, vector<int> weak, vector<int> dist) {
    memset(cache, -1, sizeof(cache));
    int ret = countMinRequired(n,0,0,0,weak,dist);
    return (ret == INF) ? -1 : ret;
}
