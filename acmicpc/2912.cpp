#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <functional>

#define newline '\n'

using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int N, C, M;
    cin >> N >> C;
    vector<int> array(N+1);
    vector<vector<int>> indexes(C+1);
    for (int i = 1; i <= N; ++i) {
        cin >> array[i];
        indexes[array[i]].push_back(i);
    }

    cin >> M;
    random_device rd;
    mt19937 re(rd());
    int lo, hi, j;
    for (int i = 0; i < M; ++i) {
        cin >> lo >> hi;
        uniform_int_distribution<> uid(lo,hi);
        auto generator = bind(uid, re);
        for (j = 0; j < 20; ++j) {
            int random = generator();
            auto& index = indexes[array[random]];
            int freq = upper_bound(index.begin(), index.end(), hi) - lower_bound(index.begin(), index.end(), lo);
            if (freq > ((hi-lo+1) >> 1)) {
                cout << "yes " << array[random] << newline;
                break;
            }
        }
        if (j == 20) cout << "no" << newline;
    }
}
