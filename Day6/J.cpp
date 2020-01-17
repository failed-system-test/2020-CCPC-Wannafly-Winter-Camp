#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
using ll = long long;
map<ll, ll> dp[52];
ll C[55][55], f[55];

ll lcm(ll a, ll b) { return a * b / __gcd(a, b); }
void init() {
    f[0] = 1;
    for (int i = 1; i <= 50; i++) f[i] = f[i - 1] * i % mod;
    C[0][0] = 1;
    for (int i = 1; i <= 50; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }
    dp[0][1] = 1;
    for (int i = 1; i <= 50; i++) {
        dp[i] = dp[i - 1];
        for (int j = 2; j <= i; j++) {
            for (auto &V : dp[i - j])
                (dp[i][lcm(j, V.first)] +=
                 V.second * C[i - 1][j - 1] % mod * f[j - 1] % mod) %= mod;
        }
    }
}
int main() {
    init();
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        ll k;
        scanf("%d%lld", &n, &k);
        ll ans = 0;
        for (auto &V : dp[n]) {
            // cerr << ": " << V.first << ' ' << V.second << endl;
            if (k % V.first == 0) (ans += V.second) %= mod;
        }
        printf("%lld\n", ans);
    }
}
