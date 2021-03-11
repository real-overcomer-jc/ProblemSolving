#include <string>
#include <vector>

using namespace std;

bool checkArea(const vector<string>& board, int startY, int startX) {
    const int H = board.size(), W = board[0].size();
    if (H < startY + 2 || W < startX + 2) return false;
    
    int blockType = -1;
    for (int y = startY; y < startY+2; ++y) {
        for (int x = startX; x < startX+2; ++x) {
            if (board[y][x] == 0) return false;
            if (blockType == -1) blockType = board[y][x];
            else if (blockType != board[y][x]) return false;
        }
    }
    return true;
}

int removeArea(vector<string>& board, int startY, int startX) {
    const int H = board.size(), W = board[0].size();
    if (H < startY + 2 || W < startX + 2) return false;
    
    int removedBlocks = 0;
    for (int y = startY; y < startY+2; ++y) {
        for (int x = startX; x < startX+2; ++x) {
            if (board[y][x] > 0) ++removedBlocks;
            board[y][x] = 0;
        }
    }
    return removedBlocks;
}

void shiftDown(vector<string>& board) {
    const int H = board.size(), W = board[0].size();
    for (int x = 0; x < W; ++x) {
        for (int y = H-2; y >= 0; --y) {
            for (int h = y; h+1 < H && board[h+1][x] == 0; ++h) {
                    board[h+1][x] = board[h][x];
                    board[h][x] = 0;
            }
        }
    }
}

int solution(int m, int n, vector<string> board) {
    const int H = board.size(), W = board[0].size();
    
    int removedBlocks = 0;
    while (true) {
        vector<pair<int,int>> removedArea;
        for (int y = 0; y < H; ++y) {
            for (int x = 0; x < W; ++x) {
                if (checkArea(board, y, x)) {
                    removedArea.push_back({y,x});
                }   
            }
        }
        
        if (removedArea.empty()) break;

        for (int i = 0; i < removedArea.size(); ++i) {
            int y = removedArea[i].first, x = removedArea[i].second;
            removedBlocks += removeArea(board, y, x);
        }
        
        shiftDown(board);
    }
    
    return removedBlocks;
}
