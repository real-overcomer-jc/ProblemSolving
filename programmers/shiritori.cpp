#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> solution(int n, vector<string> words) {
    map<string,bool> used;
    used[words[0]] = true;
    char prevLastChar = words[0].back();
    for (int i = 1; i < words.size(); ++i) {
        if (used[words[i]] || prevLastChar != words[i].front()) return {i%n+1, (i+n)/n};
        used[words[i]] = true;
        prevLastChar = words[i].back();
    }
    return {0,0};
}
