// MLE or WA
#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <local_debug.hpp>
#else
#define debug(...)
#endif

const int MAXN = 1 << 11;

using i64 = long long;

int n, m1, m2;
i64 a[MAXN][MAXN];

struct inNode {
    std::shared_ptr<inNode> lson, rson;
    i64 value;
    inNode() : value(0), lson(nullptr), rson(nullptr) {}
    void maintain() { value = std::max(lson->value, rson->value); }
};

struct outNode {
    std::shared_ptr<outNode> lson, rson;
    std::shared_ptr<inNode> value;
    outNode() : value(nullptr), lson(nullptr), rson(nullptr) {}
    void maintain() { merge(value, lson->value, rson->value, 1, n); }
    static void merge(std::shared_ptr<inNode>& o, std::shared_ptr<inNode>& ls,
                      std::shared_ptr<inNode> rs, int l, int r) {
        debug("merge", l, r);
        if (o == nullptr) {
            o = std::make_shared<inNode>();
        }
        assert(o);
        assert(ls);
        assert(rs);
        if (l == r) {
            o->value = std::max(ls->value, rs->value);
            debug(o->value, ls->value, rs->value);
            return;
        }
        const int m = l + r >> 1;
        merge(o->lson, ls->lson, rs->lson, l, m);
        merge(o->rson, ls->rson, rs->rson, m + 1, r);
        o->maintain();
    }
};

void build(std::shared_ptr<inNode>& o, int x, int l, int r) {
    if (o == nullptr) {
        o = std::make_shared<inNode>();
    }
    debug("y", l, r);
    if (l == r) {
        o->value = a[x][l];
        debug(o->value);
        return;
    }
    const int m = l + r >> 1;
    build(o->lson, x, l, m);
    build(o->rson, x, m + 1, r);
    o->maintain();
}

void build(std::shared_ptr<outNode>& o, int l, int r) {
    if (o == nullptr) {
        o = std::make_shared<outNode>();
    }
    debug("x", l, r);
    if (l == r) {
        build(o->value, l, 1, n);
        return;
    }
    const int m = l + r >> 1;
    build(o->lson, l, m);
    build(o->rson, m + 1, r);
    o->maintain();
}

i64 query(std::shared_ptr<inNode> o, int l, int r, int y1, int y2) {
    assert(o);
    debug(l, r, y1, y2);
    if (y1 <= l && r <= y2) {
        debug(o->value);
        return o->value;
    }
    const int m = l + r >> 1;
    i64 ans = 0;
    if (y1 <= m) ans = std::max(ans, query(o->lson, l, m, y1, y2));
    if (m < y2) ans = std::max(ans, query(o->rson, m + 1, r, y1, y2));
    return ans;
}

i64 query(std::shared_ptr<outNode> o, int l, int r, int x1, int x2, int y1,
          int y2) {
    assert(o);
    debug(l, r, x1, x2, y1, y2);
    if (x1 <= l && r <= x2) {
        return query(o->value, 1, n, y1, y2);
    }
    const int m = l + r >> 1;
    i64 ans = 0;
    if (x1 <= m) ans = std::max(ans, query(o->lson, l, m, x1, x2, y1, y2));
    if (m < x2) ans = std::max(ans, query(o->rson, m + 1, r, x1, x2, y1, y2));
    debug(ans);
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
    std::shared_ptr<outNode> rt = nullptr;
    build(rt, 1, n);
    for (int i = 0, x1, y1, x2, y2; i < m2; i++) {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        printf("%lld\n", query(rt, 1, n, x1, x2, y1, y2));
    }
}
