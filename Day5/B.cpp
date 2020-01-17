#include <bits/stdc++.h>

using i64 = long long;

const int MAXN = 501000;
const int MAXM = 501000;

int n, m;
int edges[MAXN][2];
int last[MAXN];
int op[MAXM];
int result[MAXN];

int main() {
    std::scanf("%d%d", &n, &m);
    for(int i = 0; i < n - 1; ++i)
        std::scanf("%d%d", &edges[i][0], &edges[i][1]), --edges[i][0], --edges[i][1], last[i] = 0;
    for(int i = 0; i < m; ++i)
        std::scanf("%d", &op[i]), --op[i];
    for(int i = 0; i < n; ++i)
        result[i] = 1;
    for(int i = m - 1; i >= 0; --i) {
        int x = op[i];
        int y = result[edges[x][0]] + result[edges[x][1]] - last[x];
        result[edges[x][0]] = result[edges[x][1]] = last[x] = y;
    }
    for(int i = 0; i < n; ++i)
        std::printf("%d%c", result[i], " \n"[i == n - 1]);
}
