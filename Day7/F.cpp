#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = 998244353;
const int inv2 = 499122177;

inline ll M(ll x) { return (x % mod + mod) % mod; }
ll sum(ll a, ll b) { return M(a + b) * M(b - a + 1) % mod * inv2 % mod; }
int main() {
    int T;
    cin >> T;
    while (T--) {
        ll n, m, x, y, k;
        cin >> n >> m >> x >> y >> k;
        ll tot = n * m;
        if (n > m) {
            swap(n, m);
            swap(x, y);
        }
        if (n == 1) {
            ll len1 = max(0LL, min(y - 1, m - y) - 1);
            ll len2 = m - len1 - 1;
            if (k <= m - len1)
                cout << sum(1, k) << endl;
            else if (k <= m + len1) {
                ll x = (k - len2) / 2;
                cout << sum(x + 1, k) << endl;
            } else
                cout << sum(k - m + 1, k) << endl;
        } else {
            if (k <= tot)
                cout << sum(1, k) << endl;
            else
                cout << sum(k - tot + 1, k) << endl;
        }
    }
}
