#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <local_debug.hpp>
#else
#define debug(...)
#endif

using i64 = long long;

i64 pow(i64 a, i64 n, int mod) {
    i64 t = 1;
    for (; n; n >>= 1, (a *= a) %= mod) {
        if (n & 1) (t *= a) %= mod;
    }
    return t;
}

const int MAXN = 1 << 20;
int inv[MAXN];

int main() {
    int T;
    scanf("%d", &T);
    std::vector<std::pair<int, int>> ans;
    while (T--) {
        int p;
        scanf("%d", &p);
        ans.clear();
        if (p <= 2) {
            puts("0");
            continue;
        }
        if (p == 3) {
            puts("1\n2 2");
            continue;
        }
        int minv = p;
        inv[1] = 1;
        for (int i = 2;; i++) {
            inv[i] = (i64)inv[p % i] * (p - p / i) % p;
            if (inv[i] < i) break;
            if (inv[i] < minv) {
                minv = inv[i];
                ans.emplace_back(i, minv);
            }
        }
        int n = ans.size();
        printf("%d\n", n * 2);
        for (int i = 0; i < n; i++) {
            printf("%d %d\n", ans[i].first, ans[i].second);
        } 
        for (int i = n - 1; ~i; i--) {
            printf("%d %d\n", ans[i].second, ans[i].first);
        } 
    }
}
