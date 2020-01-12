#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <local_debug.hpp>
#else
#define debug(...)
#endif

using i64 = long long;

int n, m;
i64 k;
const int MAXN = 1 << 17;
int a[MAXN], b[MAXN], br[MAXN];

bool check(i64 x) {
    i64 result = 0;
    for(int i = 0; i < n; ++i) {
        if(a[i] == 0) {
            if(x > 0) result += m;
        } else {
            if(a[i] > 0)
                result += std::lower_bound(b, b + m, x, [&](i64 l, i64 r) { return l * a[i] < r; }) - b;
            else
                result += std::lower_bound(br, br + m, x, [&](i64 l, i64 r) { return l * a[i] < r; }) - br;
        }
        if(result > k) return false;
    }
    return true;
}

int main() {
    scanf("%d%d%lld", &n, &m, &k);
    k = i64(n) * m - k;
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);
    for (int i = 0; i < m; i++)
        scanf("%d", b + i);
    std::sort(b, b + m);
    for(int i = 0; i < m; ++i)
        br[i] = b[m - i - 1];
    i64 l = -1.1e12, r = 1.1e12;
    while(l < r) {
        i64 mid = (l + r) >> 1;
        if(check(mid)) l = mid + 1;
        else r = mid;
    }
    std::printf("%lld\n", l - 1);
}
