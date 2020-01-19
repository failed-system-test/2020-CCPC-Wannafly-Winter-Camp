#include <bits/stdc++.h>

using i64 = long long;

i64 gcd(i64 a, i64 b) { return a ? gcd(b % a, a) : b; }

const int MAXN = 101000;

int a1, a2, b1, b2;
int n;

bool calc(i64 x) {
    i64 delta = x * (x + 1) / 2;
    return delta >= std::max(b1 - a1 * x, i64(0)) + std::max(b2 - a2 * x, i64(0));
}

int main() {
    std::scanf("%d%d%d", &a1, &a2, &n);
    i64 result = 1e18;
    for(int i = 0; i < n; ++i) {
        std::scanf("%d%d", &b1, &b2);
        i64 l = 0, r = 1e6;
        while(l < r) {
            i64 mid = (l + r) / 2;
            if(calc(mid)) r = mid;
            else l = mid + 1;
        }
        result = std::min(result, l);
    }
    std::printf("%lld\n", result);
}
