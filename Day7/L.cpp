#include <bits/stdc++.h>

using i64 = long long;

i64 gcd(i64 a, i64 b) { return a ? gcd(b % a, a) : b; }

int popcount(int x) { return __builtin_popcount(x); }

const int MAXN = 20;

int n, m, q;
int edges[MAXN];
int next[1 << MAXN];
int cnt[1 << MAXN];
int sum[MAXN][(1 << MAXN) + 1];

int main() {
    std::scanf("%d%d%d", &n, &m, &q);
    int s = 0;
    for(int i = 0; i < n; ++i) {
        int x;
        std::scanf("%d", &x);
        s |= x << i;
    }
    for(int i = 0; i < m; ++i) {
        int u, v;
        std::scanf("%d%d", &u, &v);
        --u, --v;
        edges[v] |= 1 << u;
    }
    for(int i = 0; i < (1 << n); ++i)
        next[i] = cnt[i] = -1;
    int t = s;
    int c = 0;
    while(next[t] == -1) {
        cnt[t] = c;
        int r = 0;
        for(int j = 0; j < n; ++j)
            r |= (popcount(t & edges[j]) & 1) << j;
        next[t] = r;
        t = next[t];
        ++c;
    }
    int base = cnt[t], loop = c - cnt[t];
    for(int u = s, i = 0; i < c; ++i) {
        for(int j = 0; j < n; ++j)
            sum[j][i + 1] = sum[j][i] + ((u >> j) & 1);
        u = next[u];
    }
    for(int i = 0; i < q; ++i) {
        int x;
        i64 k;
        std::scanf("%d%lld", &x, &k);
        --x;
        if(sum[x][base] == sum[x][c] && k > sum[x][base]) std::puts("-1");
        else {
            if(k <= sum[x][base]) {
                int result = std::lower_bound(sum[x], sum[x] + base + 1, k) - sum[x];
                std::printf("%d\n", result);
            } else {
                i64 result = base;
                k -= sum[x][base];
                int cc = sum[x][c] - sum[x][base];
                int l = (k + cc - 1) / cc - 1;
                result += l * loop;
                k -= cc * l;
                result += std::lower_bound(sum[x] + base + 1, sum[x] + c, k + sum[x][base]) - (sum[x] + base + 1);
                std::printf("%lld\n", result);
            }
        }
    }
}
