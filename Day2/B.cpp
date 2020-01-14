#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 55;
const int BIT = 30;
const int mod = 1e9 + 7;
int m[maxn];
ll dp[maxn];
int n, k;

ll Pow(ll a, ll b) {
    ll ret = 1;
    while (b) {
        if (b & 1) ret = ret * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ret;
}
ll inv(ll x) { return Pow(x, mod - 2); }

inline int get(int x, int i) { return (x >> i) & 1; }
inline int last(int x, int i) {
    int ret = 0;
    for (int j = 0; j <= i; j++) ret += x & (1 << j);
    return ret;
}

ll cal() {
    ll ans = 0;
    for (int i = BIT; i >= 0; i--) {
        int cnt = 0;
        for (int j = 0; j < n; j++)
            if (get(m[j], i)) cnt++;
        for (int j = 0; j < n; j++) {
            if (get(m[j], i) == 0) continue;
            memset(dp, 0, sizeof(dp));
            dp[0] = 1;
            for (int p = 0; p < n; p++) {
                if (j == p) continue;
                for (int t = cnt; t >= 0; t--) {
                    if (get(m[p], i) == 1)
                        dp[t] = (dp[t] * (1 << i) % mod +
                                 dp[t - 1] * (last(m[p], i - 1) + 1) % mod) %
                                mod;
                    else
                        dp[t] = dp[t] * (last(m[p], i - 1) + 1) % mod;
                }
            }
            for (int t = get(k, i); t <= cnt; t += 2)
                ans = (ans + dp[t] * inv(cnt - t) % mod) % mod;
        }
        if ((cnt & 1) != ((k >> i) & 1)) return ans;
    }
    return ans + 1;
}

int main() {
    while (cin >> n >> k) {
        for (int i = 0; i < n; i++) cin >> m[i];
        cout << cal() << endl;
    }
}
