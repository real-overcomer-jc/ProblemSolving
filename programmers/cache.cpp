#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>

using namespace std;

void toLowerString(string& s) {
    auto toLower = [](char ch) {
        return tolower(ch);  
    };
    transform(s.begin(), s.end(), s.begin(), toLower);
}

int solution(int cacheSize, vector<string> cities) {
    map<string,int> cache;
    map<int,string> lru;
    int totalRuntime = 0;
    for (int i = 0; i < cities.size(); ++i) {
        toLowerString(cities[i]);
        if (cache.count(cities[i]) > 0) { //hit
            lru.erase(cache[cities[i]]);
            cache[cities[i]] = i;
            lru[i] = cities[i];
            ++totalRuntime;
        } else { //miss
            if (cacheSize > 0) {
                if (cache.size() == cacheSize) {
                    cache.erase(lru.begin()->second);
                    lru.erase(lru.begin());
                } 
                cache[cities[i]] = i;
                lru[i] = cities[i];
            }
            totalRuntime += 5;
        }
    }
    return totalRuntime;
}
