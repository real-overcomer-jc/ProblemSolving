#include <string>
#include <cstring>
#include <vector>
#include <cmath>

#define y first
#define x second

using namespace std;

const vector<pair<int,int>> keyLoc = {{3,1},{0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2},{3,0},{3,2}};

int distance(int key1, int key2) {
    return abs(keyLoc[key1].y - keyLoc[key2].y) + abs(keyLoc[key1].x - keyLoc[key2].x);
}

string solution(vector<int> numbers, string hand) {
    string ret;
    char h = toupper(hand[0]);
    int lefthand = 10, righthand = 11;
    for (int i = 0; i < numbers.size(); ++i) {
        int key = numbers[i];
        if (key == 1 || key == 4 || key == 7) {
            ret.push_back('L');
            lefthand = key;
        } else if (key == 3 || key == 6 || key == 9) {
            ret.push_back('R');
            righthand = key;
        } else {
            int distFromLefthand = distance(key,lefthand);
            int distFromRighthand = distance(key,righthand);
            if (distFromLefthand == distFromRighthand) {
                ret.push_back(h);
                if (h == 'L') lefthand = key;
                else righthand = key;
            } else if (distFromLefthand < distFromRighthand) {
                ret.push_back('L');
                lefthand = key;
            } else {
                ret.push_back('R');
                righthand = key;
            }
        }
    }
    return ret;
}
