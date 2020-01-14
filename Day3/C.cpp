#include <bits/stdc++.h>

using i64 = long long;

const int MAXN = 17;

int n, m;
int edges[MAXN][MAXN];
bool vv[MAXN];
bool ve[MAXN * MAXN];
bool checked[1 << MAXN];
char dp[1 << MAXN];

bool check(const std::vector<int>& vec) {
    int s = vec.size();
    for (int i = 0; i < s - 1; ++i)
        for (int j = i + 1; j < s; ++j)
            if (edges[vec[i]][vec[j]] >= 0) return false;
    return true;
}

int main() {
    std::scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) edges[i][j] = -1;
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::scanf("%d%d", &u, &v);
        --u, --v;
        edges[u][v] = edges[v][u] = i;
    }
    std::vector<int> vec;
    vec.reserve(n);
    for (int mask = 1; mask < (1 << n); ++mask) {
        vec.clear();
        for (int i = 0; i < n; ++i)
            if ((mask >> i) & 1) vec.push_back(i);
        checked[mask] = check(vec);
    }

    dp[0] = 0;
    for (int s = 1; s < (1 << n); ++s) dp[s] = checked[s] ? 1 : n;
    for (int s = 0; s < (1 << n); ++s) {
        int r = ~s & ((1 << n) - 1);
        for (int ss = r; ss; ss = (ss - 1) & r) {
            if (!checked[ss]) continue;
            // std::cout << std::bitset<5>(s).to_string() << " -> " <<
            // std::bitset<5>(ss).to_string() << std::endl;
            dp[s | ss] = std::min(dp[s | ss], char(dp[s] + 1));
        }
    }

    // for(int i = 0; i < (1 << n); ++i)
    //    std::cout << std::bitset<5>(i).to_string() << ' ' << checked[i] << ' '
    //    << int(dp[i]) << std::endl;

    std::printf("%d\n", dp[(1 << n) - 1] - 1);
}
