#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 2e3 + 5;
ll a[maxn];

int main() {
    int n;
    scanf("%d", &n);
    ll ans = 0;
    for (int i = 0; i < n; i++) scanf("%lld", a + i);
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) ans += a[i] * a[j];
    printf("%lld\n", ans);
}
