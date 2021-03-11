#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(string skill, vector<string> skill_trees) {
    int answer = 0;
    for (auto& elem : skill_trees) {
        string ret;
        string::size_type index = 0;
        for (int i = 0; i < skill.size(); ++i) {
            index = elem.find_first_of(skill, index);
            if (index == string::npos) break;
            ret.push_back(elem[index]);
            ++index;
        }
        if (skill.find(ret) == 0) ++answer;
    }
    return answer;
}
