#include <string>
#include <vector>
#include <queue>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

using SearchInfo = tuple<int,int,int,int>;

const int bandTimeLimit = 1;

const int dy[] = {1,0,-1,0};
const int dx[] = {0,1,0,-1};

bool inRange(const vector<string>& board, int y, int x) {
    const int H = board.size(), W = board[0].size();
    return (0 <= y && y < H) && (0 <= x && x < W);
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
string solution(int m, int n, vector<string> board) {
    map<char,pair<int,int>> map;
    for (int y = 0; y < m; ++y) {
        for (int x = 0;  x < n; ++x) {
            if (isupper(board[y][x]) && map.count(board[y][x]) == 0) {
                map[board[y][x]] = {y,x};
            }
        }
    }

    string ret;
    while(map.size() > 0) {
        bool removed = false;
        for (auto pos = map.begin(); pos != map.end();) {
            char letter = pos->first;
            pair<int,int> loc = pos->second;
            
            queue<SearchInfo> q;
            for (int dir = 0; dir < 4; ++dir) {
                if (inRange(board, loc.first+dy[dir], loc.second+dx[dir]))
                    q.push(make_tuple(loc.first+dy[dir], loc.second+dx[dir], dir, 0));   
            }
            
            while (!q.empty()) {
                SearchInfo here = q.front(); q.pop(); 
                int y = get<0>(here), x = get<1>(here), dir = get<2>(here), bandTime = get<3>(here);
                //cout << letter << "," << board[y][x] << endl;
                if (!(y == loc.first && x == loc.second) && letter == board[y][x]) {
                    board[y][x] = board[loc.first][loc.second] = '.';
                    ret.push_back(letter);
                    removed = true;
                    break;
                } else if (board[y][x] != '.') {
                    continue;
                }
                
                if (inRange(board,y+dy[dir],x+dx[dir])) 
                    q.push(make_tuple(y+dy[dir],x+dx[dir],dir,bandTime));
                
                if (bandTime >= bandTimeLimit) continue;
                
                int nextDir1 = (dir+3) % 4;
                if (inRange(board,y+dy[nextDir1],x+dx[nextDir1])) 
                    q.push(make_tuple(y+dy[nextDir1],x+dx[nextDir1],nextDir1,bandTime+1));
                
                int nextDir2 = (dir+1) % 4;
                if (inRange(board,y+dy[nextDir2],x+dx[nextDir2])) 
                    q.push(make_tuple(y+dy[nextDir2],x+dx[nextDir2],nextDir2,bandTime+1));
            }

            if (board[loc.first][loc.second] == '.') {
                pos = map.erase(pos);
                break;
            } else {
                ++pos;
            }
        }

        if (!removed) {
            return "IMPOSSIBLE";
        }
    }
    return ret;
}
