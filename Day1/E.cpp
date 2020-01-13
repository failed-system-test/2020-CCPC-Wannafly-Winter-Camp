#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <local_debug.hpp>
#else
#define debug(...)
#endif

using i64 = long long;
const int MAXN = 300000 + 10;

int n, m;

std::vector<int> G[MAXN];
int dep[MAXN];
namespace lca {
std::vector<int> sp;
int dfn[MAXN];
std::pair<int, int> dp[21][MAXN << 1];

void dfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    dfn[u] = sp.size();
    sp.push_back(u);
    for (auto& v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);
        sp.push_back(u);
    }
}
void initrmq() {
    int n = sp.size();
    for (int i = 0; i < n; i++) dp[0][i] = {dfn[sp[i]], sp[i]};
    for (int i = 1; (1 << i) <= n; i++)
        for (int j = 0; j + (1 << i) - 1 < n; j++)
            dp[i][j] = std::min(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);
}
int lca(int u, int v) {
    int l = dfn[u], r = dfn[v];
    if (l > r) std::swap(l, r);
    int k = std::__lg(r - l + 1);
    return std::min(dp[k][l], dp[k][r - (1 << k) + 1]).second;
}
int dis(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }

}  // namespace lca

i64 ans[MAXN];
i64 dp[MAXN][2];

void dfs(int u, int fa) {
    for (auto& v : G[u]) {
        if (v != fa) {
            dfs(v, u);
            for (int i = 0; i < 2; i++) {
                dp[u][i] += dp[v][i];
            }
        }
    }
}

void solve(int u, int fa) {
    ans[u] += dp[u][0] * dep[u] + dp[u][1];
    for (auto& v : G[u]) {
        if (v != fa) {
            ans[v] = ans[u];
            solve(v, u);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1, u, v; i < n; i++) {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    lca::dfs(1, 0);
    lca::initrmq();

    i64 result = 0;
    debug(lca::sp);
    for (int i = 0, u, v; i < m; i++) {
        scanf("%d%d", &u, &v);
        int c = lca::lca(u, v);
        i64 l = lca::dis(u, v);
        i64 x = lca::dis(u, c);
        debug(u, v, c);
        debug(l, x);
        ans[1] += x * (l - x);
        dp[u][0] -= 2;
        dp[v][0] -= 2;
        dp[c][0] += 4;
        dp[u][1] += 1 + dep[u] * 2 - l;
        dp[v][1] += 1 + dep[v] * 2 - l;
        dp[c][1] -= (1 + dep[u] * 2 - l) + (1 + dep[v] * 2 - l);
    }
    dfs(1, 0);
    solve(1, 0);
    for (int i = 1; i <= n; i++) {
        printf("%lld\n", ans[i]);
    }
}