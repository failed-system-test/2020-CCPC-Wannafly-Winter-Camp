#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <local_debug.hpp>
#else
#define debug(...)
#endif

const int maxn = 1 << 11;
using i64 = long long;

namespace KM {
const i64 INF = 1e18;
int n;
i64 cost[maxn][maxn];
i64 lx[maxn], ly[maxn], slack[maxn];
int match[maxn];
int prev[maxn];
bool vy[maxn];

void augment(int root) {
    std::fill(vy + 1, vy + n + 1, false);
    std::fill(slack + 1, slack + n + 1, INF);
    int py;
    match[py = 0] = root;
    do {
        vy[py] = true;
        int x = match[py], yy;
        i64 delta = INF;
        for (int y = 1; y <= n; y++) {
            if (!vy[y]) {
                if (lx[x] + ly[y] - cost[x][y] < slack[y])
                    slack[y] = lx[x] + ly[y] - cost[x][y], prev[y] = py;
                if (slack[y] < delta) delta = slack[y], yy = y;
            }
        }
        for (int y = 0; y <= n; y++) {
            if (vy[y])
                lx[match[y]] -= delta, ly[y] += delta;
            else
                slack[y] -= delta;
        }
        py = yy;
    } while (match[py] != -1);
    do {
        int pre = prev[py];
        match[py] = match[pre], py = pre;
    } while (py);
}
i64 KM() {
    for (int i = 1; i <= n; i++) {
        lx[i] = ly[i] = 0;
        match[i] = -1;
        for (int j = 1; j <= n; j++) lx[i] = std::max(lx[i], cost[i][j]);
    }
    i64 answer = 0;
    for (int root = 1; root <= n; root++) augment(root);
    for (int i = 1; i <= n; i++) answer += lx[i], answer += ly[i];
    return answer;
}

}  // namespace KM

int color[maxn];

int main() {
    int n, m, k;
    auto getid = [&](int x, int y) { return (y - 1) + (x - 1) * m; };
    scanf("%d%d%d", &n, &m, &k);
    memset(KM::cost, 0xc0, sizeof(KM::cost));

    int black = 0;
    int white = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if ((i + j) & 1) {
                black++;
                color[getid(i, j)] = black;
            } else {
                white++;
                color[getid(i, j)] = -white;
            }
        }
    }

    KM::n = std::min(black, white);
    for (int i = 1; i <= KM::n; i++) {
        for (int j = 1; j <= KM::n; j++) {
            KM::cost[i][j] = 0;
        }
    }

    for (int i = 0, x1, x2, y1, y2, w; i < k; i++) {
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &w);
        int x = color[getid(x1, y1)];
        int y = color[getid(x2, y2)];
        if (x > 0) std::swap(x, y);
        debug(x, y);
        KM::cost[-x][y] = std::max<long long>(w, KM::cost[-x][y]);
    }

    printf("%lld\n", KM::KM());
}