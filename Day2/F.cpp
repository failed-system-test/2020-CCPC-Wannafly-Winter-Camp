#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 6;
using ll = long long;
using pii = pair<int, int>;
vector<pii> G[maxn];
int in[maxn], out[maxn];
int par_w[maxn], son_w[maxn];
int par[maxn], son[maxn];
ll ans[maxn];

int clk;
int sz[maxn], top[maxn];

void dfs(int u, int fa, int d) {
    par[u] = fa;
    sz[u] = 1;
    in[u] = ++clk;
    for (auto &V : G[u]) {
        int v = V.first, w = V.second;
        if (v == fa) continue;
        par_w[v] = w;
        dfs(v, u, d + 1);
        sz[u] += sz[v];
        if (son[u] == -1 || sz[v] > sz[son[u]]) son[u] = v, son_w[u] = w;
    }
    out[u] = clk;
}
void link(int u, int t) {
    top[u] = t;
    if (son[u] == -1) return;
    link(son[u], t);  // 保证重链的dfs序是连续的
    for (auto &V : G[u]) {
        int v = V.first;
        if (v != son[u] && v != par[u]) link(v, v);
    }
}

void build() {
    dfs(1, 1, 1);
    link(1, 1);
}

void update(int u, int x) {
    while (u != 1) {
        if (u == top[u]) ans[par[u]] += 1LL * par_w[u] * x;
        u = par[top[u]];
    }
}

int n, q;
ll bit[maxn];
void add(int u, int x) {
    for (int i = u; i <= n; i += i & (-i)) bit[i] += x;
}
ll query(int l, int r) {
    ll ret = 0;
    for (int i = l - 1; i > 0; i -= i & (-i)) ret -= bit[i];
    for (int i = r; i > 0; i -= i & (-i)) ret += bit[i];
    return ret;
}
ll ask(int rt, ll tot) {
    ll res = 0;
    if (par[rt]) res += 1LL * par_w[rt] * (tot - query(in[rt], out[rt]));
    if (son[rt] != -1)
        res += 1LL * son_w[rt] * (query(in[son[rt]], out[son[rt]]));
    printf("%lld\n", res + ans[rt]);
}

int main() {
    scanf("%d", &n);
    for (int i = 0, u, v, w; i < n - 1; i++) {
        scanf("%d%d%d", &u, &v, &w);
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    memset(son, -1, sizeof(son));
    build();
    scanf("%d", &q);
    ll tot = 0;
    int op, v, x, rt = 1;
    while (q--) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &v, &x);
            tot += x;
            add(in[v], x);
            update(v, x);
            ask(rt, tot);
        } else {
            scanf("%d", &v);
            rt = v;
            ask(rt, tot);
        }
    }
}
