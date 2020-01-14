#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 2000;
const int N = 710000;
int MOD;

int b[maxn], c[maxn][maxn], Inv[maxn + 10];
ll sqr, n;  /// sqr为sqrt(n)
ll w[N], id1[N], id2[N];

int tot;  ///记录对于要筛的n,sqrt(n)以内质数的个数
int isp[N], p[N];
ll zh[N][3];  /// zh[i][k]记录(p[1])^k + (p[2])^k + ... + (p[i])^k
ll g[N][3];

ll poww(ll a, int b) {
    ll ans = 1, base = a % MOD;
    while (b) {
        if (b & 1) {
            ans *= base;
            ans %= MOD;
        }
        base *= base;
        base %= MOD;
        b >>= 1;
    }
    return ans;
}

ll sigma_f(ll n, int k) {
    if (k == 0) return n;
    n++;
    n %= MOD;
    ll tmp = n;
    ll ans = 0;
    for (int i = 1; i <= k + 1; i++) {
        ans += 1LL * c[k + 1][i] * b[k + 1 - i] % MOD * n % MOD;
        ans %= MOD;
        n *= tmp % MOD;
        n %= MOD;
    }
    ans *= Inv[k + 1];
    ans %= MOD;
    ans += MOD;
    ans %= MOD;
    return ans;
}

void get_p(int n, int w) {
    tot = 0;
    memset(isp, 1, sizeof(isp));
    isp[0] = 0;
    isp[1] = 0;
    for (int i = 2; i <= n; i++) {
        if (isp[i]) {
            p[++tot] = i;
            ll wait = 1;
            for (int j = 0; j <= w; j++) {
                zh[tot][j] = zh[tot - 1][j] + wait;
                zh[tot][j] %= MOD;
                wait *= i;
            }
        }

        for (int j = 1; p[j] * i <= n && j <= i; j++) {
            isp[i * p[j]] = 0;
            if (i % p[j] == 0) break;
        }
    }
}

void get_g(ll n, int t) {
    int m = 0;
    ll i = 1, r;
    while (i <= n) {
        ll len = n / i;
        r = n / len;
        if (len <= sqr)
            id1[len] = ++m;
        else
            id2[r] = ++m;
        for (int ww = 0; ww <= t; ww++) {
            g[m][ww] = sigma_f(len, ww) - 1;
            g[m][ww] %= MOD;
            g[m][ww] += MOD;
            g[m][ww] %= MOD;
        }
        w[m] = len;  /// w[i]记录了形如n/k的第i大的取值是多少
        i = r + 1;
    }

    for (int i = 1; i <= tot; i++) {
        for (int j = 1; j <= m; j++) {
            if (1LL * p[i] * p[i] > w[j])
                break;
            else {
                int op;
                if (w[j] / p[i] <= sqr)
                    op = id1[w[j] / p[i]];
                else
                    op = id2[n / (w[j] / p[i])];
                for (int ww = 0; ww <= t; ww++) {
                    g[j][ww] =
                        g[j][ww] -
                        poww(p[i], ww) * ((g[op][ww] - zh[i - 1][ww]) % MOD);
                    g[j][ww] %= MOD;
                    g[j][ww] += MOD;
                    g[j][ww] %= MOD;
                }
            }
        }
    }
}

inline ll get_value(int wz, int k) {
    ll w = (g[wz][2] + g[wz][1] - g[wz][0]) -
           (zh[k - 1][2] + zh[k - 1][1] - zh[k - 1][0]);
    w %= MOD;
    w += MOD;
    w %= MOD;
    return w;
}

ll f(ll p, ll k) {
    if (k == 1) return (p * p + p - 1) % MOD;
    return ((poww(p, 2 * k) + poww(p, 2 * k - 1) - poww(p, k - 1)) % MOD +
            MOD) %
           MOD;
}

ll get_s(ll x, int k) {
    if (x <= 1 || p[k] > x) return 0;
    int wz;
    if (x <= sqr)
        wz = id1[x];
    else
        wz = id2[n / x];
    ll ans = get_value(wz, k);
    for (int i = k; i <= tot && 1LL * p[i] * p[i] <= x; ++i) {
        for (ll l = p[i], e = 1; l * p[i] <= x; l = l * p[i], ++e) {
            ans = ans + (get_s(x / l, i + 1) * f(p[i], e) % MOD) % MOD +
                  f(p[i], e + 1);
            ans %= MOD;
        }
    }
    ans += MOD;
    ans %= MOD;
    return ans;
}

void init() {
    c[0][0] = 1;
    for (int i = 1; i < maxn; i++) {
        for (int j = 1; j <= i; j++)
            c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
        c[i][0] = 1;
    }
    Inv[1] = 1;
    for (int i = 2; i < maxn; i++)
        Inv[i] = 1LL * Inv[MOD % i] * (MOD - MOD / i) % MOD;
    b[0] = 1;
    for (int i = 1; i < maxn; i++) {
        b[i] = 0;
        for (int k = 0; k < i; k++)
            b[i] = (b[i] + 1LL * c[i + 1][k] * b[k] % MOD) % MOD;
        b[i] = (1LL * b[i] * (-Inv[i + 1]) % MOD + MOD) % MOD;
    }
}

void solve(ll n) {
    init();
    sqr = sqrt(n);
    get_p(sqr, 2);
    get_g(n, 2);
    ll ans = get_s(n, 1) + 1;
    printf("%lld\n", ans);
}

int main() {
    std::scanf("%lld%d", &n, &MOD);
    solve(n);
}
