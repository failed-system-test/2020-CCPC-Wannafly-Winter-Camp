#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <local_debug.hpp>
#else
#define debug(...)
#endif

const int MAXN = 105;
char s[MAXN][MAXN];
int d[MAXN][MAXN];

int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
int dy[] = {1, -1, 2, -2, 2, -2, 1, -1};
int cx[] = {-1, -1, 0, 0, 0, 0, 1, 1};
int cy[] = {0, 0, 1, -1, 1, -1, 0, 0};

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%s", s[i]);
    }
    memset(d, -1, sizeof(d));
    std::queue<int> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'M') {
                q.push(i * m + j);
                d[i][j] = 0;
            }
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        int x = u / m;
        int y = u % m;
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || ny < 0 || nx >= n || ny >= m || s[nx][ny] != '.' ||
                ~d[nx][ny])
                continue;
            int cxx = x + cx[i];
            int cyy = y + cy[i];
            if (cxx < 0 || cyy < 0 || cxx >= n || cyy >= m ||
                s[cxx][cyy] == 'X')
                continue;
            d[nx][ny] = d[x][y] + 1;
            q.push(nx * m + ny);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d%c", d[i][j], " \n"[j == m - 1]);
        }
    }
}
