#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define newline '\n'

using namespace std;

struct Query {
    int l, r, idx;
};

const int MAX = 1e6+1;
long long freq[MAX], sum;

void add(int n) {
    sum -= freq[n] * freq[n] * n;
    ++freq[n];
    sum += freq[n] * freq[n] * n;
}

void sub(int n) {
    sum -= freq[n] * freq[n] * n;
    --freq[n];
    sum += freq[n] * freq[n] * n;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<int> array(N+1);
    for (int i = 1; i <= N; ++i) {
        cin >> array[i];
    }

    vector<Query> query(M);
    for (int i = 0; i < M; ++i) {
        cin >> query[i].l >> query[i].r;
        query[i].idx = i;
    }

    const int sqrtN = sqrt(N);
    auto criterion = [&](const Query& q1, const Query& q2) {
        int b1 = q1.r / sqrtN;
        int b2 = q2.r / sqrtN;
        return (b1 == b2) ? q1.l < q2.l : b1 < b2;
    };
    sort(query.begin(), query.end(), criterion);

    vector<long long> ret(M);
    int lo = query[0].l, hi = query[0].r;
    for (int i = lo; i <= hi; ++i) {
        add(array[i]);
    }
    ret[query[0].idx] = sum;

    for (int i = 1; i < M; ++i) {
        Query& q = query[i];
        while (lo < q.l) sub(array[lo++]);
        while (lo > q.l) add(array[--lo]);
        while (hi < q.r) add(array[++hi]);
        while (hi > q.r) sub(array[hi--]);
        ret[q.idx] = sum;
    }

    for (auto result : ret) cout << result << newline;
}
