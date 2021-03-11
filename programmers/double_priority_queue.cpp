#include <string>
#include <vector>
#include <set>

using namespace std;

vector<int> solution(vector<string> operations) {
    multiset<int> ordered;
    for (auto& command : operations) {
        if (command[0] == 'I') {
            ordered.insert(stoi(command.substr(2)));
        } else {
            if (ordered.size() > 0) {
                if (command[2] == '1') {
                    ordered.erase(prev(ordered.end()));
                } else {
                    ordered.erase(ordered.begin());
                }
            }
        }
    }
    if (ordered.size() == 0) return {0,0};
    return {*prev(ordered.end()),*ordered.begin()};
}
