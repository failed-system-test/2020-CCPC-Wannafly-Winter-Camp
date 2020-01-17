#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <local_debug.hpp>
#else
#define debug(...)
#endif

using i64 = long long;

const int MAXN = 1 << 17;
int a[MAXN];
i64 f[MAXN];

const int mod = 119 << 23 | 1;
i64 pow(i64 a, i64 n, int mod) {
    i64 t = 1;
    assert(n >= 0);
    for (; n; n >>= 1, (a *= a) %= mod)
        if (n & 1) (t *= a) %= mod;
    return t;
}

i64 inv(i64 a, int mod) { return pow(a, mod - 2, mod); }

i64 sqr2 = 116195171;
const int N = 1 << 17;
const int G = 3;
i64 wn[N << 2], rev[N << 2];
int NTT_init(int n_) {
    int step = 0;
    int n = 1;
    for (; n < n_; n <<= 1) ++step;
    for (int i = 1; i < n; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (step - 1));
    int g = pow(G, (mod - 1) / n, mod);
    wn[0] = 1;
    for (int i = 1; i <= n; ++i) wn[i] = wn[i - 1] * g % mod;
    return n;
}

void NTT(i64 a[], int n, int f) {
    for (int i = 0; i < n; i++)
        if (i < rev[i]) std::swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += (k << 1)) {
            int t = n / (k << 1);
            for (int j = 0; j < k; j++) {
                i64 w = f == 1 ? wn[t * j] : wn[n - t * j];
                i64 x = a[i + j];
                i64 y = a[i + j + k] * w % mod;
                a[i + j] = (x + y) % mod;
                a[i + j + k] = (x - y + mod) % mod;
            }
        }
    }
    if (f == -1) {
        i64 ninv = inv(n, mod);
        for (int i = 0; i < n; i++) a[i] = a[i] * ninv % mod;
    }
}

i64 aa[N << 2], bb[N << 2], conv[N << 2];

int main() {
    int n;
    assert(pow(sqr2, 2, mod) == 2);
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        f[a[i]]++;
    }

    for (int i = 0; i < 100001; i++) {
        aa[i] = f[i] * pow(sqr2, (i64)i * i, mod) % mod;
        bb[i] = pow(sqr2, (-(i64)i * i) % (mod - 1) + mod - 1, mod);
    }

    int m = NTT_init(1 << 18);
    NTT(aa, m, 1);
    NTT(bb, m, 1);
    for (int i = 0; i < m; i++) {
        conv[i] = aa[i] * bb[i] % mod;
    }
    NTT(conv, m, -1);

    i64 ans = 0;
    for (int i = 0; i < 100001; i++) {
        ans = ans + f[i] * pow(sqr2, (i64)i * i, mod) % mod * conv[i] % mod;
        ans %= mod;
    }
    ans = ans * 2 % mod;
    for (int i = 0; i < 100001; i++) {
        ans = ans - f[i] * f[i] % mod * pow(2, (i64)i * i, mod) % mod;
        ans = (ans + mod) % mod;
    }
    printf("%lld\n", ans);
}
