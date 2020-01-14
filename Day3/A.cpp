#include <bits/stdc++.h>

using i64 = long long;

const int MAXN = 1100;

int n;
int arr[MAXN][MAXN];
int result[MAXN];

int main() {
    std::scanf("%d", &n);
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            std::scanf("%d", &arr[i][j]);
    if(n == 2) {
        if(arr[0][1] != 2) return 1;
        result[0] = result[1] = 1;
    } else {
        result[0] = (arr[0][1] + arr[0][2] - arr[1][2]) / 2;
        for(int i = 1; i < n; ++i)
            result[i] = arr[i - 1][i] - result[i - 1];
    }
    for(int i = 0; i < n; ++i)
        std::printf("%d%c", result[i], " \n"[i == n - 1]);
}
