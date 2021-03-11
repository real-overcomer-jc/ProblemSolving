#include <string>
#include <vector>

using namespace std;

vector<vector<int>> rotate(const vector<vector<int>> dimension) {
    const int H = dimension.size(), W = dimension[0].size();
    vector<vector<int>> rotated(W, vector<int>(H,0));
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            rotated[x][H-1-y] = dimension[y][x];
        }
    }
    return rotated;
}

bool inRange(const vector<vector<int>>& dimension, int y, int x) {
    const int H = dimension.size(), W = dimension[0].size();
    return (0 <= y && y < H) && (0 <= x && x < W);
}

bool isFullyFilled(const vector<vector<int>>& dimension) {
    const int H = dimension.size(), W = dimension[0].size();
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            if (dimension[y][x] == 0 || dimension[y][x] > 1) return false; 
        }
    }
    return true;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    const int lockHeight = lock.size(), lockWidth = lock[0].size();
    for (int i = 0; i < 4; ++i) {
        int keyHeight = key.size(), keyWidth = key[0].size();
        for (int startY = -keyHeight+1; startY < lockHeight; ++startY) {
            for (int startX = -keyWidth+1; startX < lockWidth; ++startX) {
                vector<vector<int>> target = lock;
                for (int y = 0; y < keyHeight; ++y) {
                    for (int x = 0; x < keyWidth; ++x) {
                        if (!inRange(lock, startY+y, startX+x)) continue;
                        //if (target[startY+y][startX+x]) continue;
                        target[startY+y][startX+x] += key[y][x];
                    }
                }
                if (isFullyFilled(target)) return true;
            }
        }
        key = rotate(key);
    }
    return false;
}

