#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    unordered_map<string,int> completionMap;
    for (auto& name : completion) {
        ++completionMap[name];
    }
    
    for (auto& name : participant) {
        if(completionMap[name] == 0) {
            return name;
        } else {
            --completionMap[name];
        }
    }
    return "--oops--";
}

/*string solution(vector<string> participant, vector<string> completion) {
    sort(participant.begin(), participant.end());
    sort(completion.begin(), completion.end());
    
    for (int i = 0; i < completion.size(); ++i) {
        if (participant[i] != completion[i])
            return participant[i];
    }
    return participant.back();
}*/
