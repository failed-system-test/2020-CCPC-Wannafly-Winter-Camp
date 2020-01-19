#include <bits/stdc++.h>

using i64 = long long;

i64 gcd(i64 a, i64 b) { return a ? gcd(b % a, a) : b; }

const int MAXN = 110;

int n, MOD;
i64 fac[MAXN];

i64 pow64(i64 a, i64 b) {
    a = (a % MOD + MOD) % MOD;
    i64 result = 1;
    while(b) {
        if(b & 1) result = result * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return result;
}
i64 inv64(i64 a) { return pow64(a, MOD - 2); }
i64 cc(i64 a, i64 b) { return fac[a] * inv64(fac[b] * fac[a - b]) % MOD; }

i64 calc(int n) {
    i64 result = cc(2 * n, n);
    for(int i = 0; i < n; ++i)
        result = ((result - pow64(2, n - i - 1) * cc(2 * i, i)) % MOD + MOD) % MOD;
    return result;
}

int main() {
    std::scanf("%d%d", &n, &MOD);
    fac[0] = fac[1] = 1;
    for(int i = 2; i < MAXN; ++i)
        fac[i] = fac[i - 1] * i % MOD;
    i64 result = calc(n);
    std::printf("%lld\n", result);
}