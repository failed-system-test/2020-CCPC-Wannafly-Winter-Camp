#include <bits/stdc++.h>
using namespace std;
const int maxn = 55;
int a[maxn], mx[maxn][maxn], sum[maxn][maxn];
int dp[maxn][maxn], cost[maxn][maxn];

int cal(int x) {
    if (x <= 3) return 1;
    x -= 3;
    return (x + 1) / 2 + 1;
}

int main() {
    int T, n;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", a + i);
        for (int i = 1; i <= n; i++) {
            mx[i][i] = a[i];
            sum[i][i] = a[i];
            cost[i][i] = 0;
            for (int j = i + 1; j <= n; j++) {
                mx[i][j] = max(a[j], mx[i][j - 1]);
                sum[i][j] = sum[i][j - 1] + a[j];
                cost[i][j] = mx[i][j] * (j - i + 1) - sum[i][j];
            }
        }
        memset(dp, 0, sizeof(dp));
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                dp[i][j] = dp[i - 1][j];
                for (int k = i; i - k + 1 <= 2 * j + 1 && k > 0; k--) {
                    int tmp = cal(i - k + 1);
                    dp[i][j] = max(dp[i][j], dp[k - 1][j - tmp] + cost[k][i]);
                    // cerr << "i = " << i << "  j = " << j
                    //  << "  ans = " << dp[i][j] << endl;
                }
            }
        }
        for (int i = 1; i <= n; i++)
            printf("%d%c", dp[n][i] + sum[1][n], i == n ? '\n' : ' ');
    }
}
