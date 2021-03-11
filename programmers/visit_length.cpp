#include <map>

using namespace std;

struct Point {
    int y, x;
    Point(int y, int x) : y(y), x(x) {}
    bool operator==(const Point& rhs) const {
        return y == rhs.y && x == rhs.x;
    }
    bool operator<(const Point& rhs) const {
        return y < rhs.y || !(rhs.y < y) && (x < rhs.x);  
    }
};

struct Line {
    Point p1, p2;
    Line(Point p1, Point p2) : p1(p1), p2(p2) {
        if (p2 < p1) swap(this->p1,this->p2);
    }
    bool operator==(const Line& rhs) const {
        //return (p1 == rhs.p1 && p2 == rhs.p2) || (p1 == rhs.p2 && p2 == rhs.p1);
        return (p1 == rhs.p1 && p2 == rhs.p2);
    }
    bool operator<(const Line& rhs) const {
        return p1 < rhs.p1 || !(rhs.p1 < p1) && p2 < rhs.p2;
    }
};

struct LineHasher {
    size_t operator()(const Line& rhs) const {
        return hash<int>()(rhs.p1.x) ^ hash<int>()(rhs.p1.y) ^ hash<int>()(rhs.p2.x) ^ hash<int>()(rhs.p2.y);
    }
};

bool inRange(int y, int x) {
    return (0 <= y && y <= 10) && (0 <= x && x <= 10);
}

int solution(string dirs) {
    map<Line,bool> map;

    int ret = 0;
    Point p1(5,5), p2(5,5);
    for (int i = 0; i < dirs.size(); ++i) {
        bool canMove = false;
        if (dirs[i] == 'U' && inRange(p1.y-1,p1.x)) {
            p2 = Point(p1.y-1,p1.x);
            canMove = true;
        } else if (dirs[i] == 'D' && inRange(p1.y+1,p1.x)) {
            p2 = Point(p1.y+1,p1.x);
            canMove = true;
        } else if (dirs[i] == 'R' && inRange(p1.y,p1.x+1)) {
            p2 = Point(p1.y,p1.x+1);
            canMove = true;
        } else if (dirs[i] == 'L' && inRange(p1.y,p1.x-1)) {
            p2 = Point(p1.y,p1.x-1);
            canMove = true;
        } 
        
        if (canMove) {
            if (map.count(Line(p1,p2)) == 0) ++ret;
            map[Line(p1,p2)] = true;
            p1 = p2;
        }
    }
    return ret;
}
