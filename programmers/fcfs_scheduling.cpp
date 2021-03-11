#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

int solution(int n, vector<int> cores) {
    if (n < cores.size()) return n;

    int lo = 0, hi = ((n+cores.size()-1)/cores.size())*10000;
    while (lo <= hi) {
        int mid = lo + (hi-lo)/2;
        int throughput = 0; //finished + ongoing + allocated;
        int allocated = 0;
        for (int time : cores) {
            throughput += (mid/time)+1;
            if (mid%time == 0) ++allocated;
        }
        
        if (n <= throughput - allocated) {
            hi = mid-1;
        } else if (n > throughput) {
            lo = mid+1;
        } else {
            int remainder = n - (throughput - allocated);
            int count = 0;
            for (int i = 0; i < cores.size(); ++i) {
                if (mid%cores[i] == 0) ++count;
                if (remainder == count) return i+1;
            }
        }
    }
    return -1;
}
