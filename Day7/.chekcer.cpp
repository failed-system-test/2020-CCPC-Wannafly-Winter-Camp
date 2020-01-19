#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

const int MAXN = 100005;
const int MAXT = 155;

/// inner dp
int cnt, bx[35], by[35], bz[35], bit[5][5][2];
map<int, int> mp;
int tot, st[MAXT], go[MAXT][6];
void build() {
    for (int i = 0; i <= 4; i++)
        for (int j = i; j <= 4; j++)
            for (int k = 0; k < 2; k++) {
                bx[cnt] = i, by[cnt] = j, bz[cnt] = k;
                bit[i][j][k] = cnt++;
            }
    mp[1 << bit[0][0][0]] = tot;
    st[tot++] = (1 << bit[0][0][0]);
    queue<int> q;
    q.push(1 << bit[0][0][0]);
    while (!q.empty()) {
        int s = q.front();
        q.pop();
        for (int g = 0; g <= 5; g++) {
            int tb = 0;
            for (int b = 0; b < cnt; b++)
                if (s >> b & 1) {
                    int t1 = bx[b], t2 = by[b], t3 = g, p = bz[b];
                    if (t3 < t2) continue;
                    t2 -= t1, t3 -= t1;
                    if (t3 < 5) tb |= (1 << bit[t2][t3][p]);
                    if (!p && t3 - 2 >= t2) tb |= (1 << bit[t2][t3 - 2][1]);
                    if (t3 - 3 >= t2) tb |= (1 << bit[t2][t3 - 3][p]);
                    if (!p && t3 - 5 >= t2) tb |= (1 << bit[t2][t3 - 5][1]);
                }
            if (mp.find(tb) == mp.end()) {
                mp[tb] = tot;
                st[tot++] = tb;
                q.push(tb);
            }
            go[mp[s]][g] = mp[tb];
        }
    }
}

/// outer dp
int dp[2][MAXT][2];
int check(int n, int ca) {
    vector<int> cnt(n + 1);
    int k = ouf.readInt(0, 2 * n);
    for (int i = 1; i <= 3 * k + 1; i++) cnt[ouf.readInt(1, n)]++;
    for (int i = 1; i <= n; i++)
        if (cnt[i] > 4)
            quitf(_wa,
                  "In case %d, the number of tile %d is %d, which is greater "
                  "than 4.",
                  ca, i, cnt[i]);
    int now = 0, la = 1;
    for (int j = 0; j < MAXT; j++) dp[now][j][0] = dp[now][j][1] = 0;
    dp[now][mp[1 << bit[0][0][0]]][0] = 1;
    for (int i = 1; i <= n; i++) {
        swap(now, la);
        for (int j = 0; j < MAXT; j++) dp[now][j][0] = dp[now][j][1] = 0;
        for (int j = 0; j < MAXT; j++)
            for (int c = 0; c < 2; c++)
                if (dp[la][j][c])
                    for (int g = 0; c + g < 2; g++)
                        dp[now][go[j][g + cnt[i]]][c + g] += dp[la][j][c];
    }
    int res = 0;
    for (int j = 0; j < MAXT; j++)
        if (st[j] >> bit[0][0][1] & 1) res += dp[now][j][1];
    return res;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    build();
    int T = inf.readInt();
    for (int ca = 1; ca <= T; ca++) {
        int n = inf.readInt(), L = inf.readInt(), res = check(n, ca);
        if (res != L)
            quitf(_wa,
                  "In case %d, the number of kinds of waiting tiles is %d, but "
                  "%d expected.",
                  ca, res, L);
    }
    quitf(_ok, "%d cases", T);
    return 0;
}
