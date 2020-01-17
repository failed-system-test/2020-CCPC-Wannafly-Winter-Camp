#include <bits/stdc++.h>

using i64 = long long;

const int MAXN = 110;

int t, n;
int arr[MAXN];

int main() {
    std::scanf("%d", &t);
    for(int test = 0; test < t; ++test) {
        std::scanf("%d", &n);
        for(int i = 0; i < n; ++i)
            std::scanf("%d", &arr[i]);
        std::vector<int> result(n);
        int cur = 0;
        int cnt = 0;
        for(int i = 1; ; ++i) {
            while(cur < n && result[cur]) ++cur;
            if(cur == n) break;
            if(arr[cur] == -1) arr[cur] = i;
            for(int j = n - 1; j >= cur; --j)
                if(arr[j] == i)
                    result[j] = ++cnt;
        }
        for(int i = 0; i < n; ++i)
            std::printf("%d%c", result[i], " \n"[i == n - 1]);
    }
}
