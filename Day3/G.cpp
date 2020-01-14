#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
const int maxn = 5e5 + 5;
int n, k;
vector<pii> G[maxn];
bool key[maxn];
ll dep[maxn];
ll go[maxn], back[maxn];
ll ans[maxn];
multiset<ll> dep_son[maxn];

ll dfs(int u, int fa, ll h) {
    dep[u] = h;
    if (key[u]) dep_son[u].insert(h);
    go[u] = 0;
    for (auto &V : G[u]) {
        int v = V.first, w = V.second;
        if (v == fa) continue;
        ll tmp = dfs(v, u, h + w);
        if (tmp != -1) {
            dep_son[u].insert(tmp);
            go[u] += back[v] + 2LL * w;
        }
    }
    back[u] = go[u];
    if (!dep_son[u].empty()) {
        go[u] -= *dep_son[u].rbegin() - dep[u];
        return *dep_son[u].rbegin();
    }
    return -1;
}

void gao(int u, int fa, ll back_fa, ll dep_fa, bool ok) {
    // cerr << "-> " << u << " " << fa << ' ' << back_fa << ' ' << dep_fa << ' '
    // << ok << endl;
    ans[u] = back[u] + back_fa - dep_fa;
    for (auto &V : G[u]) {
        int v = V.first, w = V.second;
        if (v == fa) continue;
        ll nxt_fa, nxt_dep;
        bool nxt_ok = true;

        if (!dep_son[v].empty())
            dep_son[u].erase(dep_son[u].find(*dep_son[v].rbegin()));

        if (dep_son[u].empty()) {
            if (ok)
                nxt_dep = dep_fa + w, nxt_fa = back_fa + 2LL * w;
            else
                nxt_dep = 0, nxt_fa = 0, nxt_ok = false;
        } else {
            nxt_dep = w + max(dep_fa, *dep_son[u].rbegin() - dep[u]);
            nxt_fa = back_fa + back[u] - back[v];
            if (dep_son[v].empty()) nxt_fa += 2LL * w;
        }
        gao(v, u, nxt_fa, nxt_dep, nxt_ok);
        if (!dep_son[v].empty()) dep_son[u].insert(*dep_son[v].rbegin());
    }
    if (!dep_son[u].empty())
        ans[u] = ans[u] + dep_fa - max(dep_fa, *dep_son[u].rbegin() - dep[u]);
}
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0, u, v, w; i < n - 1; i++) {
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    for (int i = 0, x; i < k; i++) {
        scanf("%d", &x);
        key[x] = 1;
    }
    dfs(1, 1, 0LL);
    gao(1, 1, 0, 0, 0);
    for (int i = 1; i <= n; i++) printf("%lld\n", ans[i]);
}
