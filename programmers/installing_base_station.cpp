#include <iostream>
#include <vector>
using namespace std;

int solution(int n, vector<int> stations, int w)
{
    stations.push_back(n+1+w);
    const int coverageLen = 2*w + 1;
    int loc = 1, installed = 0;
    for (auto& stationLoc : stations) {
        if (stationLoc-w > loc) {
            int remainder = stationLoc-w-loc;
            installed += (remainder + coverageLen-1) / coverageLen;
        }
        loc = stationLoc+w+1;
    }
    return installed;
}
