#include <bits/stdc++.h>

using i64 = long long;

const int MAXN = 1100;
const int MAXM = 1100;
const int MAXS = 110;

int decode(char c) { return c >= 'a' && c <= 'z' ? c - 'a' : c - 'A' + 26; }
char encode(int x) { return x <= 25 ? x + 'a' : x - 26 + 'A'; }

int n, m;
int x[MAXM], y[MAXM];
char str[MAXN][MAXS];
int len[MAXN];

int main() {
    std::scanf("%d%d", &n, &m);
    for(int i = 0; i < m; ++i)
        std::scanf("%d%d", &x[i], &y[i]), --x[i], --y[i];
    for(int i = 0; i < n; ++i)
        std::scanf("%s", str[i]), len[i] = std::strlen(str[i]);
    for(int i = m - 1; i >= 0; --i)
        for(int j = 0; j < len[y[i]]; ++j)
            str[y[i]][j] = encode((decode(str[y[i]][j]) - decode(str[x[i]][j % len[x[i]]]) + 52) % 52);
    for(int i = 0; i < n; ++i)
        std::puts(str[i]);
}
