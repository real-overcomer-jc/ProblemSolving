#include <string>
#include <vector>
#include <map>

using namespace std;

map<string,int> nClothesMap;

int solution(vector<vector<string>> clothes) {
    for (auto& coll : clothes) {
        nClothesMap[coll.back()] += 1;
    }
    
    int ret = 1;
    for (auto& entry : nClothesMap) {
        ret *= entry.second + 1;
    }
    return ret - 1;
}
