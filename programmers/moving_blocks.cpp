#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct Point {
    int y, x;
    Point(int _y, int _x) : y(_y), x(_x) {}
    bool operator==(const Point& rhs) const {
        return y == rhs.y && x == rhs.x;
    }
    bool operator<(const Point& rhs) const {
        return y < rhs.y || !(rhs.y < y) && x < rhs.x; 
    }
    Point operator+(const Point& rhs) const {
        return Point(y+rhs.y, x+rhs.x);
    }
    Point operator-(const Point& rhs) const {
        return Point(y-rhs.y, x-rhs.x);
    }
};

using Vector = Point;

enum Direction {DOWN, RIGHT, UP, LEFT};
enum Pivot{FRONT, BACK};

vector<Vector> rotated{Vector(1,0),Vector(0,1),Vector(-1,0),Vector(0,-1)};
map<Vector,int> rotatedNo{{Vector(1,0),0},{Vector(0,1),1},{Vector(-1,0),2},{Vector(0,-1),3}};

struct State {
    const vector<vector<int>> board;
    Point p;
    Vector v;
    State(const vector<vector<int>> _board, Point _p, Vector _v) : board(_board), p(_p), v(_v) {}
    bool operator<(const State& rhs) const {
        return p < rhs.p || !(rhs.p < p) && v < rhs.v; 
    }
    bool inRange(Point p) {
        return (0 <= p.y && p.y < board.size()) && (0 <= p.x && p.x < board[0].size());
    }
    void shift(int direction) {
        Point p1 = p + rotated[direction], p2 = p + v + rotated[direction];
        if (!inRange(p1) || !inRange(p2) || board[p1.y][p1.x] || board[p2.y][p2.x]) return;
        p = p1;
    }
    void rotate(Pivot pivot, int delta) {
        Point p1 = p;
        Vector v1 = v, v2 = rotated[(rotatedNo[v] + delta + 4) % 4];
        if (pivot == BACK) {
            p1 = p + v;
            v1 = rotated[(rotatedNo[v] + 2) % 4];
            v2 = rotated[(rotatedNo[v1] + delta + 4) % 4];
        }
        
        Point cp = p1 + (v1 + v2);
        Point tp = p1 + v2;
        if (!inRange(cp) || !inRange(tp) || board[cp.y][cp.x] || board[tp.y][tp.x]) return;
        
        v = v2;
        if (pivot == BACK) {
            p = tp;
            v = rotated[(rotatedNo[v2] + 2) % 4];
        }
    }
    vector<State> adjacent() {
        vector<State> ret(8, *this);
        for (int i = 0; i < 4; ++i) {
            ret[i].shift(i);
        }
        ret[4].rotate(FRONT, 1);
        ret[5].rotate(FRONT, -1);
        ret[6].rotate(BACK, 1);
        ret[7].rotate(BACK, -1);
        return ret;
    }
};

int solution(vector<vector<int>> board) {
    Point endPoint(board.size()-1, board[0].size()-1);
    map<State,int> dist;
    queue<State> q;
    //q.push(State(board, Point(0,0), Vector(1,0)));
    q.push(State(board, Point(0,0), Vector(0,1)));
    //dist[State(board, Point(0,0), Vector(1,0))] = 0;
    dist[State(board, Point(0,0), Vector(0,1))] = 0;               
    while (!q.empty()) {
        State current = q.front(); q.pop();
        //if (current.p == endPoint || current.p + current.v == endPoint) return dist[current];
        
        for (auto& next : current.adjacent()) {
            if (dist.count(next) > 0) continue;
            if (next.p == endPoint || next.p + next.v == endPoint) return dist[current]+1;
            dist[next] = dist[current]+1;
            q.push(next);
        }
    }
    return -1;
}
