#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>

#define newline '\n'

using namespace std;

struct Query {
    int l, r, idx;
};

int freq[(int)1e6+1], distinctNumbers;

void add(int n) {
    if (++freq[n] == 1) ++distinctNumbers;
}

void sub(int n) {
    if (--freq[n] == 0) --distinctNumbers;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    memset(freq, 0, sizeof freq);

    int N;
    cin >> N;
    vector<int> array(N+1, 0);
    for (int i = 1; i <= N; ++i) {
        cin >> array[i];
    }

    int M;
    cin >> M;
    vector<Query> queries(M);
    for (int i = 0; i < M; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].idx = i;
    }

    const int sqrtN = sqrt(N);
    auto criterion = [&](const Query& q1, const Query& q2) {
        int b1 = q1.r / sqrtN;
        int b2 = q2.r / sqrtN;
        return (b1 == b2) ? q1.l < q2.l : b1 < b2;
    };
    sort(queries.begin(), queries.end(), criterion);

    vector<int> ret(M,0);
    int lo = queries[0].l, hi = queries[0].r;
    for (int i = lo; i <= hi; ++i) {
        add(array[i]);
    }
    ret[queries[0].idx] = distinctNumbers;

    for (int i = 1; i < M; ++i) {
        Query& query = queries[i];
        while (lo < query.l) sub(array[lo++]);
        while (lo > query.l) add(array[--lo]);
        while (hi < query.r) add(array[++hi]);
        while (hi > query.r) sub(array[hi--]);
        ret[query.idx] = distinctNumbers;
    }

    for (int result : ret) {
        cout << result << newline;
    }
}
