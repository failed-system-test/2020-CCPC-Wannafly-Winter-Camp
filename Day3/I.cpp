#include <bits/stdc++.h>

using i64 = long long;

i64 exgcd(i64 a, i64 b, i64& x, i64& y) {
    i64 d = a;
    if(b) d = exgcd(b, a % b, y, x), y -= x * (a / b);
    else x = 1, y = 0;
    return d;
}
bool excrt(i64* r, i64* m, i64 n, i64& re, i64& mo) {
    i64 x, y;
    mo = m[0], re = r[0];
    for(int i = 1; i < n; i++) {
        i64 d = exgcd(mo, m[i],  x, y);
        if((r[i] - re) % d != 0) return 0;
        x = (r[i] - re) / d * x % (m[i] / d);
        re += x * mo;
        mo = mo / d * m[i];
        re %= mo;
    }
    re = (re + mo) % mo;
    return 1;
}

const int MAXN = 20;
const int MAXT = 51000;

int t;
i64 r[MAXT], m[MAXT];

double dp[MAXN][MAXN][MAXN];

double solve(i64 n) {
    if(n >= MAXN) return 0;
    
    dp[1][1][0] = 1;
    dp[2][1][0] = 1;
    dp[2][1][1] = 0;
    dp[2][2][0] = 0.5;
    dp[2][2][1] = 0.5;
    
    for(int i = 3; i <= n; ++i)
        for(int j = 1; j <= i; ++j)
            for(int k = 0; k < i; ++k) {
                if(k < j) {
                    double sum = 0;
                    for(int l = 0; l < j; ++l) {
                        double x = 100;
                        if(l == k) {
                            if(j > 1) x = std::min(x, dp[i - 1][std::max(j - 2, 1)][i - 2]);
                            if(j < i) x = std::min(x, dp[i - 1][std::max(j - 1, 1)][i - 2]);
                        } else {
                            if(j > 2) {
                                if(k > 1 && l < k)
                                    x = std::min(x, dp[i - 1][std::max(j - 2, 1)][k - 2]);
                                if(k > 0 && k < j - 1)
                                    x = std::min(x, dp[i - 1][std::max(j - 2, 1)][k - 1]);
                                if(k < j - 1 && l > k && !(k == j - 2 && l == j - 1))
                                    x = std::min(x, dp[i - 1][std::max(j - 2, 1)][k]);
                            }
                            if(j < i) {
                                if(l < k) x = std::min(x, dp[i - 1][std::max(j - 1, 1)][k - 1]);
                                if(l > k) x = std::min(x, dp[i - 1][std::max(j - 1, 1)][k]);
                            }
                        }
                        sum += x;
                    }
                    dp[i][j][k] = sum / j;
                } else {
                    double x = 100;
                    if(j > 1) x = std::min(x, dp[i - 1][std::max(j - 2, 1)][k - 2]);
                    if(k > j) x = std::min(x, dp[i - 1][std::max(j - 1, 1)][k - 2]);
                    if(k < i - 1) x = std::min(x, dp[i - 1][std::max(j - 1, 1)][k - 1]);
                    dp[i][j][k] = x;
                }
                //std::cout << i << ' ' << j << ' ' << k << " = " << dp[i][j][k] << std::endl;
            }
    return dp[n][n][0];
}

int main() {
    std::scanf("%d", &t);
    for(int i = 0; i < t; ++i)
        std::scanf("%lld%lld", &r[i], &m[i]);
    i64 re, mo;
    if(!excrt(r, m, t, re, mo) || re < 2) std::puts("error");
    else {
        double result = solve(re);
        std::printf("0.%06d\n", int(std::round(result * 1000000)));
    }
}
