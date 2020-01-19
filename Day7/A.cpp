#include <bits/stdc++.h>
using namespace std;
#define lson (rt << 1)
#define rson (rt << 1 | 1)
#define Lson l, m, lson
#define Rson m + 1, r, rson
const int mod = 1e9 + 7;
const int maxn = 1e5 + 5;
using ll = long long;
ll pow2[maxn];
int a[maxn], pos[maxn];
ll le[maxn][2], ri[maxn][2];
ll ans[maxn];
ll sum[maxn << 2];

void build(int l, int r, int rt) {
    sum[rt] = 0;
    if (l == r) return;
    int m = l + r >> 1;
    build(Lson);
    build(Rson);
}
void update(int l, int r, int rt, int p, ll x) {
    if (l == r) {
        (sum[rt] += x) %= mod;
        return;
    }
    int m = l + r >> 1;
    if (p <= m)
        update(Lson, p, x);
    else
        update(Rson, p, x);
    sum[rt] = sum[lson] + sum[rson];
}
ll query(int l, int r, int rt, int L, int R) {
    if (L > R) return 0;
    if (L <= l && R >= r) return sum[rt];
    int m = l + r >> 1;
    ll ret = 0;
    if (L <= m) (ret += query(Lson, L, R)) %= mod;
    if (m + 1 <= R) (ret += query(Rson, L, R)) %= mod;
    return ret;
}

int main() {
    pow2[0] = 1;
    for (int i = 1; i < maxn; i++) pow2[i] = pow2[i - 1] * 2LL % mod;

    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%d", a + i), pos[a[i]] = i;

    build(1, n, 1);
    for (int i = 1; i <= n; i++) {
        le[a[i]][0] = query(1, n, 1, a[i] + 2, n);
        le[a[i]][1] = query(1, n, 1, 1, a[i] - 2);
        update(1, n, 1, a[i], pow2[i - 1]);
    }

    build(1, n, 1);
    for (int i = n; i >= 1; i--) {
        ri[a[i]][0] = query(1, n, 1, a[i] + 2, n);
        ri[a[i]][1] = query(1, n, 1, 1, a[i] - 2);
        update(1, n, 1, a[i], pow2[n - i]);
    }

    // for (int i = 1; i <= n; i++) {
    //     cerr << "val = " << i << endl;
    //     cerr << "le :" << le[i][0] << ' ' << le[i][1] << endl;
    //     cerr << "ri :" << ri[i][0] << ' ' << ri[i][1] << endl;
    // }

    ans[1] = 0;
    for (int i = 1; i < n; i++) {
        ans[i + 1] = ans[i];
        ll tmp = (le[i][0] * pow2[n - pos[i]] % mod +
                  ri[i][0] * pow2[pos[i] - 1] % mod) %
                 mod;
        ans[i + 1] = (ans[i + 1] + tmp) % mod;

        tmp = (le[i + 1][1] * pow2[n - pos[i + 1]] % mod +
               ri[i + 1][1] * pow2[pos[i + 1] - 1] % mod) %
              mod;
        ans[i + 1] = (ans[i + 1] - tmp + mod) % mod;
    }
    for (int i = 1; i <= n; i++) printf("%lld\n", ans[i]);
}
