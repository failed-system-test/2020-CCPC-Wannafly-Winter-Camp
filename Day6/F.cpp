#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <local_debug.hpp>
#else
#define debug(...)
#endif

using i64 = long long;

const int MAXN = 5100;

struct E { int u, v; };

int n;
i64 a, b, c, p, d;
int degree[MAXN];

int main() {
    scanf("%d", &n);
    scanf("%lld%lld%lld%lld%lld", &a, &b, &c, &p, &d);
    for(int i = 1; i < n; ++i)
        for(int j = i + 1; j <= n; ++j)
            if((a * i64(i + j) * (i + j) + b * i64(i - j) * (i - j) + c) % p > d) {
                ++degree[i], ++degree[j];
            }
    i64 result = i64(n) * (n - 1) * (n - 2) / 6;
    i64 sum = 0;
    for(int i = 1; i <= n; ++i)
        sum += i64(degree[i]) * (n - 1 - degree[i]);
    result -= sum / 2;
    std::printf("%lld\n", result);
    
}
