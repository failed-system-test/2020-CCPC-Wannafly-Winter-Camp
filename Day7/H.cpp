#include <bits/stdc++.h>

using i64 = long long;

i64 gcd(i64 a, i64 b) { return a ? gcd(b % a, a) : b; }

int n;

int main() {
    std::scanf("%d", &n);
    int a = 0;
    for(int i = 1; i <= n; ++i)
        for(int j = i + 1; j <= n; ++j)
            a += gcd(i, j) == 1;
    int b = (n - 1) / 2 * 2 + 1;
    if(!a) b = 1;
    else {
        int g = gcd(a, b);
        a /= g, b /= g;
    }
    std::printf("%d/%d\n", a, b);
}
