#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <local_debug.hpp>
#else
#define debug(...)
#endif

using i64 = long long;
const int MAXN = 1 << 12;
i64 tree[MAXN][MAXN];
int n, m1, m2;
i64 a[MAXN][MAXN];

inline int id(int l, int r) { return l + r | l != r; }
#define o id(l, r)
#define lson id(l, m)
#define rson id(m + 1, r)

void merge(i64* tree, i64* ls, i64* rs, int l, int r) {
    if (l == r) {
        tree[o] = std::max(ls[o], rs[o]);
        return;
    }
    const int m = l + r >> 1;
    merge(tree, ls, rs, l, m);
    merge(tree, ls, rs, m + 1, r);
    tree[o] = std::max(tree[lson], tree[rson]);
}

void build(int x, i64* tree, int l, int r) {
    if (l == r) {
        tree[o] = a[x][l];
        return;
    }
    const int m = l + r >> 1;
    build(x, tree, l, m);
    build(x, tree, m + 1, r);
    tree[o] = std::max(tree[lson], tree[rson]);
}

void build(int l, int r) {
    if (l == r) {
        build(l, tree[o], 1, n);
        return;
    }
    const int m = l + r >> 1;
    build(l, m);
    build(m + 1, r);
    merge(tree[o], tree[lson], tree[rson], 1, n);
}

i64 query(i64* tree, int l, int r, int y1, int y2) {
    if (y1 <= l && r <= y2) {
        return tree[o];
    }
    const int m = l + r >> 1;
    i64 ans = 0;
    if (y1 <= m) ans = std::max(ans, query(tree, l, m, y1, y2));
    if (m < y2) ans = std::max(ans, query(tree, m + 1, r, y1, y2));
    return ans;
}

i64 query(int l, int r, int x1, int x2, int y1, int y2) {
    if (x1 <= l && r <= x2) {
        return query(tree[o], 1, n, y1, y2);
    }
    const int m = l + r >> 1;
    i64 ans = 0;
    if (x1 <= m) ans = std::max(ans, query(l, m, x1, x2, y1, y2));
    if (m < x2) ans = std::max(ans, query(m + 1, r, x1, x2, y1, y2));
    return ans;
}

int main() {
    scanf("%d%d%d", &n, &m1, &m2);
    for (int i = 0, x1, y1, x2, y2, w; i < m1; i++) {
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &w);
        a[x1][y1] += w;
        a[x1][y2 + 1] -= w;
        a[x2 + 1][y1] -= w;
        a[x2 + 1][y2 + 1] += w;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] += a[i - 1][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            a[i][j] += a[i][j - 1];
        }
    }
    build(1, n);
    for (int i = 0, x1, y1, x2, y2; i < m2; i++) {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        printf("%lld\n", query(1, n, x1, x2, y1, y2));
    }
}
