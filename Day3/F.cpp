#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5 + 5;
int n, k;
int a[maxn], b[maxn];
ll dp[maxn][22], cost;

void add(int x) {
    cost += b[a[x]];
    b[a[x]]++;
}
void del(int x) {
    b[a[x]]--;
    cost -= b[a[x]];
}
void solve(int L, int R, int l, int r, int t) {
    // cost(l, L);
    if (L > R) return;
    int MID = L + R >> 1, mid, right = min(r, MID);
    for (int i = L + 1; i <= MID; i++) add(i);
    for (int i = l; i <= right; i++) {
        del(i);
        ll tmp = dp[i][t - 1] + cost;
        if (dp[MID][t] > tmp) {
            dp[MID][t] = tmp;
            mid = i;
        }
    }

    // cost(mid, MID + 1);
    for (int i = right; i >= mid; i--) add(i);
    add(MID + 1);
    solve(MID + 1, R, mid, r, t);

    // cost(l, L);
    for (int i = mid - 1; i >= l; i--) add(i);
    for (int i = MID + 1; i > L; i--) del(i);
    solve(L, MID - 1, l, mid, t);
}
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= k; j++) dp[i][j] = 1e18;
    dp[0][0] = 0;

    for (int i = 1; i <= k; i++) {
        cost = 0;
        memset(b, 0, sizeof(b));
        add(0), add(1);
        solve(1, n, 0, n, i);
    }
    printf("%lld\n", dp[n][k]);
}
