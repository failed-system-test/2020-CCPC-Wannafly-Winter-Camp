#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
using ll = long long;
int a[405][200000];
ll ans[405];

ll Pow(ll a, ll b) {
    ll ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ret;
}

inline void add(int& x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}

inline void sub(int& x, int y) {
    x -= y;
    if (x < 0) x += mod;
}

const int maxn = 1 << 14;
ll f[maxn];
ll inv[maxn];
void CalFact() {
    f[0] = 1;
    for (int i = 1; i < maxn; i++) f[i] = (f[i - 1] * i) % mod;
    inv[maxn - 1] = Pow(f[maxn - 1], mod - 2);
    for (int i = maxn - 2; ~i; i--) inv[i] = inv[i + 1] * (i + 1) % mod;
}

using VI = vector<int>;
ll res[maxn], base[maxn], _c[maxn], _md[maxn];
vector<int> Md;
void mul(ll* a, ll* b, int k) {
    for (int i = 0; i < k + k; i++) _c[i] = 0;
    for (int i = 0; i < k; i++)
        if (a[i])
            for (int j = 0; j < k; j++)
                _c[i + j] = (_c[i + j] + a[i] * b[j]) % mod;
    for (int i = k + k - 1; i >= k; i--)
        if (_c[i])
            for (int j = 0; j < Md.size(); j++)
                _c[i - k + Md[j]] =
                    (_c[i - k + Md[j]] - _c[i] * _md[Md[j]]) % mod;
    for (int i = 0; i < k; i++) a[i] = _c[i];
}
int solve(ll n, VI a, VI b) {
    ll ans = 0, pnt = 0;
    int k = a.size();
    assert(a.size() == b.size());
    for (int i = 0; i < k; i++) _md[k - 1 - i] = -a[i];
    _md[k] = 1;
    Md.clear();
    for (int i = 0; i < k; i++)
        if (_md[i] != 0) Md.push_back(i);
    for (int i = 0; i < k; i++) res[i] = base[i] = 0;
    res[0] = 1;
    while ((1LL << pnt) <= n) pnt++;
    for (int p = pnt; p >= 0; p--) {
        mul(res, res, k);
        if ((n >> p) & 1) {
            for (int i = k - 1; i >= 0; i--) res[i + 1] = res[i];
            res[0] = 0;
            for (int j = 0; j < Md.size(); j++)
                res[Md[j]] = (res[Md[j]] - res[k] * _md[Md[j]]) % mod;
        }
    }
    for (int i = 0; i < k; i++) ans = (ans + res[i] * b[i]) % mod;
    if (ans < 0) ans += mod;
    return ans;
}
VI BM(VI s) {
    VI C(1, 1), B(1, 1);
    int L = 0, m = 1, b = 1;
    for (int n = 0; n < s.size(); n++) {
        ll d = 0;
        for (int i = 0; i <= L; i++) d = (d + (ll)C[i] * s[n - i]) % mod;
        if (d == 0)
            ++m;
        else if (2 * L <= n) {
            VI T = C;
            ll c = mod - d * Pow(b, mod - 2) % mod;
            while (C.size() < B.size() + m) C.push_back(0);
            for (int i = 0; i < B.size(); i++)
                C[i + m] = (C[i + m] + c * B[i]) % mod;
            L = n + 1 - L, B = T, b = d, m = 1;
        } else {
            ll c = mod - d * Pow(b, mod - 2) % mod;
            while (C.size() < B.size() + m) C.push_back(0);
            for (int i = 0; i < B.size(); i++)
                C[i + m] = (C[i + m] + c * B[i]) % mod;
            ++m;
        }
    }
    return C;
}
int gao(VI a, ll n) {
    VI c = BM(a);
    c.erase(c.begin());
    // std::cerr << c.size() << std::endl;
    for (int i = 0; i < c.size(); i++) c[i] = (mod - c[i]) % mod;
    // for(auto & t : c) {
    //     printf("%d,", t);
    // }
    // puts("");
    return solve(n, c, VI(a.begin(), a.begin() + c.size()));
}

int main() {
    int n, k;
    CalFact();
    scanf("%d%d", &n, &k);
    a[1][0] = 1;
    for (int i = 2; i <= (k + 1) * 4; i++) {
        int cnt = (i - 2) * (i - 1) / 2;
        for (int j = 0; j <= cnt; j++) {
            add(a[i][j], a[i - 1][j]);
            sub(a[i][j + i], a[i - 1][j]);
        }
        cnt = i * (i - 1) / 2;
        for (int j = 1; j <= cnt; j++) add(a[i][j], a[i][j - 1]);
        for (int j = 0; j <= cnt; j++) (ans[i] += Pow(j, k) * a[i][j]) %= mod;
        // for(int j=0;j<=cnt;j++) cerr << a[i][j] << ' ';
        // cerr << ans[i];
        // cerr << endl;
    }
    std::vector<int> vec;
    for (int i = 1; i <= (k + 1) * 4; i++) {
        vec.push_back(ans[i] * inv[i] % mod);
    }
    
    ll ans = gao(vec, n - 1);
    for (int i = 0; i < n; i++) ans = ans * (i + 1) % mod;
    printf("%lld\n", ans);
}
