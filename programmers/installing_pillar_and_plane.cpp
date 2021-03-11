#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

const int PILLAR = 0, PLANE = 1;
const int REMOVE = 0, INSTALL = 1;

vector<vector<int>> pillarInstalled;
vector<vector<int>> planeInstalled;

int N;

bool hasPillar(int x, int y) {
    if (x < 0 || y < -1 || x > N || y >= N) return false;
    return y == -1 || pillarInstalled[x][y];
}

bool hasPlane(int x, int y) {
    if (x < 0 || y < 0 || x >= N || y > N) return false;
    return y != 0 && planeInstalled[x][y];
}

bool canInstallPillar(int x, int y) {
    return hasPillar(x,y-1) || hasPlane(x-1,y) || hasPlane(x,y);
}

bool canInstallPlane(int x, int y) {
    return hasPillar(x,y-1) || hasPillar(x+1,y-1) || hasPlane(x-1,y) && hasPlane(x+1,y);
}

bool installPillar(int x, int y) {
    if (canInstallPillar(x,y)) {
        ++pillarInstalled[x][y];
        return true;
    }
    return false;
}

bool installPlane(int x, int y) {
    if (canInstallPlane(x,y)) {
        ++planeInstalled[x][y];
        return true;
    }
    return false;
}

bool checkPillar(int x, int y) {
    if (!hasPillar(x,y)) return true;
    return canInstallPillar(x,y);
}

bool checkPlane(int x, int y) {
    if (!hasPlane(x,y)) return true;
    return canInstallPlane(x,y);
}

bool removePillar(int x, int y) {
    --pillarInstalled[x][y];
    if (!checkPillar(x,y+1) || !checkPlane(x-1,y+1) || !checkPlane(x,y+1)) {
        ++pillarInstalled[x][y];
        return false;
    }
    return true;
}

bool removePlane(int x, int y) {
    --planeInstalled[x][y];
    if (!checkPillar(x,y) || !checkPillar(x+1,y) || !checkPlane(x-1,y) || !checkPlane(x+1,y)) {
        ++planeInstalled[x][y];
        return false;
    }
    return true;
}

bool runCommand(const vector<int>& command) {
    int x = command[0], y = command[1], type = command[2], job = command[3];
    if (job == INSTALL) {
        if (type == PILLAR) {
            return installPillar(x,y);
        } else { //PLANE
            return installPlane(x,y);
        }
    } else { //REMOVE
        if (type == PILLAR) {
            return removePillar(x,y);
        } else { //PLANE
            return removePlane(x,y);
        }
    }
    return false;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    ::N = n;
    pillarInstalled = planeInstalled = vector<vector<int>>(n+1, vector<int>(n+1,0));
    vector<vector<int>> ret;
    for (auto& command : build_frame) {
        if(runCommand(command)) {
            if (command[3] == REMOVE) {
                auto it = find(ret.begin(), ret.end(), vector<int>(command.begin(), command.begin()+3));
                if (it != ret.end()) ret.erase(it);
            } else {
                ret.push_back(vector<int>(command.begin(), command.begin()+3));
            }
        }
    }
    sort(ret.begin(), ret.end());
    return ret;
}
