#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#define newline '\n'

using namespace std;

struct Query {
    int l, r, idx;
};

const int MAX = 1e5+1;

int freq1[MAX], freq2[MAX], maxFreq;

void add(int n) {
    --freq2[freq1[n]];
    if (freq1[n] == maxFreq) {
        ++maxFreq;
    }
    ++freq2[++freq1[n]];
}

void sub(int n) {
    --freq2[freq1[n]];
    if (freq1[n] == maxFreq && freq2[freq1[n]] == 0) {
        --maxFreq;
    }
    ++freq2[--freq1[n]];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    int N, M;
    cin >> N;
    vector<int> array(N+1);
    for (int i = 1; i <= N; ++i) {
        cin >> array[i];
    }

    cin >> M;
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

    vector<int> ret(M);
    int lo = query[0].l, hi = query[0].r;
    for (int i = lo; i <= hi; ++i) {
        add(array[i]);
    }
    ret[query[0].idx] = maxFreq;

    for (int i = 1; i < M; ++i) {
        Query& q = query[i];
        while (lo < q.l) sub(array[lo++]); 
        while (lo > q.l) add(array[--lo]); 
        while (hi < q.r) add(array[++hi]);
        while (hi > q.r) sub(array[hi--]);
        ret[q.idx] = maxFreq; 
    }

    for (int result : ret) cout << result << newline;
}
