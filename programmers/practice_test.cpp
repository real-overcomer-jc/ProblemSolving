#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<vector<int>> students{{1, 2, 3, 4, 5}, {2, 1, 2, 3, 2, 4, 2, 5}, {3, 3, 1, 1, 2, 2, 4, 4, 5, 5}}; 
vector<int> scores{0, 0, 0};
                                                                 
vector<int> solution(vector<int> answers) {
    for (int i = 0; i < answers.size(); ++i) {
        int answer = answers[i];
        for (int j = 0; j < 3; ++j) {
            int mod = students[j].size(); 
            if (answer == students[j][i%mod])
                ++scores[j];
        }
    }
    
    vector<int> ordered{1,2,3};
    auto criterion = [](int i, int j) {
        return scores[i-1] > scores[j-1];
    };
    sort(ordered.begin(), ordered.end(), criterion);
    
    int i = 1;
    for (; i < 3; ++i) {
        if (scores[ordered[i-1]-1] != scores[ordered[i]-1]) 
            break;
    }
    ordered.erase(ordered.begin()+i, ordered.end());
    return ordered;
}
