#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <local_debug.hpp>
#else
#define debug(...)
#endif

using i64 = long long;

const int mod = 119 << 23 | 1;

i64 solve(int n, int ml, int mr) {
    i64 nn =  i64(n) * (n - 1) / 2 % mod;
    i64 result = 0;
    for (int l = 2, r; l <= mr; l = r + 1) {
        r = std::min(mr, n / (n / l));
        if(r < ml) continue;
        l = std::max(ml, l);
        i64 len = r - l + 1;
        i64 nk = n / l;
        i64 kk = i64(l + r) * len / 2 % mod;
        result = ((result + (nn - nk * n) % mod * len + (nk + 1) * nk / 2 % mod * kk) % mod + mod) % mod;
    }
    return result;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, l, r;
        scanf("%d%d%d", &n, &l, &r);
        i64 result = solve(n, l, r);
        std::printf("%lld\n", result);
    }
}
