#include <vector>
#include <map>
#include <cstring>
#include <iostream>

using namespace std;

const int dy[] = {-1,1,0,0};
const int dx[] = {0,0,-1,1};

int M,N;
int visited[100][100];
map<int,int> areaInfoMap; //area no, size

    
bool inRange(int y, int x) {
    return (0 <= y && y < M) && (0 <= x && x < N); 
}
    
void dfs(const vector<vector<int>>& picture, int y, int x, int area_no) {
    visited[y][x] = 1;
    ++areaInfoMap[area_no]; 
    
    for (int dir = 0; dir < 4; ++dir) 
        if (inRange(y+dy[dir],x+dx[dir]) && !visited[y+dy[dir]][x+dx[dir]] && picture[y+dy[dir]][x+dx[dir]] == picture[y][x]) 
            dfs(picture,y+dy[dir],x+dx[dir],area_no);
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    ::M = m, ::N = n;
    memset(visited, 0, sizeof visited);
    areaInfoMap.clear();
    
    int number_of_area = 0;
    int max_size_of_one_area = 0;
    for (int y = 0; y < m; ++y) {
        for (int x = 0; x < n; ++x) {
            if (picture[y][x] == 0) continue;
            if (!visited[y][x]) dfs(picture,y,x,number_of_area++);
        }
    }
    
    for (auto& entry : areaInfoMap) {
        if (max_size_of_one_area < entry.second) {
            max_size_of_one_area = entry.second;
        }
    }
    
    vector<int> answer(2);
    answer[0] = number_of_area;
    answer[1] = max_size_of_one_area;
    return answer;
}
