#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int rangeSum(int psum[], int i, int j) {
    return psum[j] - psum[i-1];
}

vector<int> solution(int N, vector<int> stages) {
    int count[N+2];
    memset(count, 0, sizeof(count));
    
    for (int i = 0; i < stages.size(); ++i) {
        ++count[stages[i]];
    }
    
    int psum[N+2];
    memset(psum, 0, sizeof(psum));
    
    psum[0] = count[0];
    for (int i = 1; i <= N+1; ++i) {
        psum[i] = psum[i-1] + count[i];
    }
    
    vector<double> failure(N+1,0.0);
    for (int i = 1; i <= N; ++i) {
        double denominator = static_cast<double>(rangeSum(psum, i, N+1));
        if (denominator == 0.0) failure[0] = 0;
        else failure[i] = count[i] / denominator; 
    }
    
    vector<int> ret(N,0);
    for (int i = 0; i < N; ++i) {
        ret[i] = i+1;
    }
    
    auto criterion = [&] (int i, int j) {
        if (failure[i] > failure[j]) {
            return true;
        }  else if (failure[i] == failure[j] && i < j) {
            return true;
        }
        return false;
    };
    
    sort(ret.begin(), ret.end(), criterion);
    return ret;
}
