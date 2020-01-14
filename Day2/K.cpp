#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <local_debug.hpp>
#else
#define debug(...)
#endif

const int MAXN = 500005;

struct Trie {
    int ch[MAXN][26], f[MAXN], val[MAXN], len[MAXN];
    int sz, rt;
    int newnode() {
        memset(ch[sz], -1, sizeof(ch[sz])), val[sz] = INT_MAX;
        return sz++;
    }
    void init() { sz = 0, rt = newnode(); }
    inline int idx(char c) { return c - 'a'; };
    void insert(const char* s, int x) {
        int u = 0;
        for (int i = 0; s[i]; i++) {
            int c = idx(s[i]);
            if (ch[u][c] == -1) ch[u][c] = newnode();
            u = ch[u][c];
        }
        len[u] = std::strlen(s);
        val[u] = std::min(val[u], x);
    }

    std::vector<int> G[MAXN];

    void build() {
        std::queue<int> q;
        f[rt] = rt;
        for (int c = 0; c < 26; c++) {
            if (~ch[rt][c])
                f[ch[rt][c]] = rt, q.push(ch[rt][c]);
            else
                ch[rt][c] = rt;
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int c = 0; c < 26; c++) {
                if (~ch[u][c])
                    f[ch[u][c]] = ch[f[u]][c], q.push(ch[u][c]);
                else
                    ch[u][c] = ch[f[u]][c];
            }
        }
        for (int i = 1; i < sz; i++) {
            G[f[i]].push_back(i);
        }
        dfs(rt, rt);
    }
    void dfs(int u, int cur) {
        f[u] = cur;
        if (len[u]) cur = u;
        for (auto& v : G[u]) {
            dfs(v, cur);
        }
    }
} ac;

char buf[MAXN];

using i64 = long long;

const i64 INF = 1e18;

i64 dp[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    ac.init();
    for (int i = 0, x; i < n; i++) {
        scanf("%s%d", buf, &x);
        ac.insert(buf, x);
    }
    ac.build();
    scanf("%s", buf);
    n = std::strlen(buf);
    std::fill(dp + 1, dp + n + 1, INF);
    dp[0] = 0;
    int u = ac.rt;
    for (int i = 0; buf[i]; i++) {
        u = ac.ch[u][buf[i] - 'a'];
        int v = u;
        do {
            if (ac.len[v]) {
                dp[i + 1] =
                    std::min(dp[i + 1], dp[i + 1 - ac.len[v]] + ac.val[v]);
            }
            v = ac.f[v];
        } while (v != ac.rt);
    }
    if (dp[n] == INF) dp[n] = -1;
    printf("%lld\n", dp[n]);
}