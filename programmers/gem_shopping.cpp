#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>

using namespace std;

vector<int> solution(vector<string> gems) {
    map<string,int> gemsMap;
    int n = 0;
    for (int i = 0; i < gems.size(); ++i) {
        if (gemsMap.count(gems[i]) == 0) {
            gemsMap[gems[i]] = 0;
            ++n;
        }
    }
    
    vector<int> candidate{0,(int)gems.size()};
    set<string> gemsSet;
    int tail = 0, prev = -1;
    for (int head = 0; head < gems.size(); ++head) {
        if (tail < head) tail = head;
        while (tail < gems.size()) {
            if (prev != tail) { 
                ++gemsMap[gems[tail]];
                gemsSet.insert(gems[tail]);
            }
            
            if (gemsSet.size() == n) {
                //cout << "head = " << head << ", tail = " << tail << endl;
                if ((tail-head+1) < (candidate[1]-candidate[0]+1)) {
                    candidate[0] = head; candidate[1] = tail;
                }
                break;
            }
            ++tail;
        }
        if (--gemsMap[gems[head]] == 0) gemsSet.erase(gems[head]);
        prev = tail;
    }
    return {candidate[0]+1,candidate[1]+1};
}
