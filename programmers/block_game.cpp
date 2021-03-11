#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

const int BLACK_BLK_NO = -1;

int checkRect(const vector<vector<int>>& board, int startY, int startX, int height, int width) {
    const int H = board.size(), W = board[0].size();
    if (H < startY+height || W < startX+width) return -1;

    int blockNo = -1, blockCnt = 0;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int boxValue = board[startY+y][startX+x];
            if (boxValue == 0) {
                return -1;
            } else if (boxValue > 0) {
                if (blockNo == -1) blockNo = boxValue;
                else if (blockNo != boxValue) return -1;
                ++blockCnt;
            }
        }
    }
    if (blockCnt != 4) return -1;
    return blockNo;
}

void putBlackBlocks(vector<vector<int>>& board) {
    const int H = board.size(), W = board[0].size();
    for (int x = 0; x < W; ++x) {
        for (int y = 0; y < H; ++y) {
            if (board[y][x] > 0) {
                if (y > 0) board[y-1][x] = BLACK_BLK_NO;
                if (y > 1) board[y-2][x] = BLACK_BLK_NO;
                break;
            }
        }
    }
}

void removeBlocks(vector<vector<int>>& board, const vector<int>& blocks) {
    const int H = board.size(), W = board[0].size();
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            if (board[y][x] == 0) continue;
            if (board[y][x] == BLACK_BLK_NO) {
                board[y][x] = 0;
                continue;
            } 
            auto it = find(blocks.begin(), blocks.end(), board[y][x]);
            if (it != blocks.end()) board[y][x] = 0;
        }
    }
}

int solution(vector<vector<int>> board) {
    const int H = board.size(), W = board.size();
    int count = 0;
    while (true) {
        putBlackBlocks(board);
        vector<int> blocks;
        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                int ret1 = checkRect(board, y, x, 2, 3);
                int ret2 = checkRect(board, y, x, 3, 2);
                if (ret1 > 0) { ++count; blocks.push_back(ret1); }
                if (ret2 > 0) { ++count; blocks.push_back(ret2); }
            }
        }
        if (blocks.empty()) break;
        removeBlocks(board, blocks);
    }
    return count;
}
