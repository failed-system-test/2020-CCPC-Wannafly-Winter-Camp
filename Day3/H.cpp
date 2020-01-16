#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define Lson l, m, lson
#define Rson m + 1, r, rson
#define lson_len (len - (len >> 1))
#define rson_len (len >> 1)
const int maxn = 2e5 + 5;
int a[maxn], pos[maxn];
ll seg[maxn << 2];
int lazy[maxn << 2], Max[maxn << 2];

inline void pushup(int rt) {
    seg[rt] = seg[lson] + seg[rson];
    Max[rt] = max(Max[lson], Max[rson]);
}
void build(int l, int r, int rt) {
    lazy[rt] = 0;
    if (l == r) {
        seg[rt] = l - 1;
        Max[rt] = l - 1;
        return;
    }
    int m = l + r >> 1;
    build(Lson);
    build(Rson);
    pushup(rt);
}

inline void pushdown(int rt, int len) {
    int &x = lazy[rt];
    if (!x) return;
    seg[lson] = 1LL * x * lson_len;
    seg[rson] = 1LL * x * rson_len;
    Max[lson] = x;
    Max[rson] = x;
    lazy[lson] = x;
    lazy[rson] = x;
    x = 0;
}
ll update(int l, int r, int rt, int L, int R, int x) {
    if (L > R) return 0;
    ll ret = 0;
    int m = l + r >> 1;
    if (L <= l && R >= r) {
        ll tmp = 1LL * (r - l + 1) * x;
        ret += tmp - seg[rt];
        seg[rt] = tmp;
        lazy[rt] = x;
        Max[rt] = x;
        return ret;
    }
    pushdown(rt, r - l + 1);
    if (L <= m) ret += update(Lson, L, R, x);
    if (m + 1 <= R) ret += update(Rson, L, R, x);
    pushup(rt);
    return ret;
}
int query(int l, int r, int rt, int x) {
    if (Max[rt] < x) return r;
    if (l == r) return -1;
    pushdown(rt, r - l + 1);
    int m = l + r >> 1;
    if (Max[lson] > x) return query(Lson, x);
    return max(m, query(Rson, x));
}
int n;
ll gao(int L, int R) {
    if (L > R) return 0;
    int pos = query(1, n, 1, R);
    if (pos == -1) return 0;
    ll ret = update(1, n, 1, L, pos, R);
    return ret;
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        build(1, n, 1);
        int mx = 0;
        memset(pos, -1, sizeof(pos));
        for (int i = 1; i <= n; i++)
            scanf("%d", a + i), pos[a[i]] = i, mx = max(mx, a[i]);
        ll ans = 0;
        for (int i = mx; i >= 1; i--) {
            vector<int> b;
            for (int j = i; j <= mx; j += i)
                if (pos[j] != -1) b.push_back(pos[j]);
            if (b.size() >= 2) {
                sort(b.begin(), b.end());
                int lmx = b[b.size() - 2] - 1, lmi;
                ll num = 0;
                num += gao(1, lmx);
                lmi = b[0] + 1, lmx = b.back() - 1;
                num += gao(lmi, lmx);
                lmi = b[1] + 1;
                num += gao(lmi, n);
                ans += num * i;
            }
        }
        printf("%lld\n", ans);
    }
}
