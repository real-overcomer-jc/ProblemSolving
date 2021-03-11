#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) {
    vector<int> ret;
    for (auto& command : commands) {
        vector<int> subArray(array.begin()+command[0]-1, array.begin()+command[1]);
        sort(subArray.begin(), subArray.end());
        ret.push_back(subArray[command[2]-1]);
    }
    return ret;
}
