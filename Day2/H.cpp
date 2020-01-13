#include <bits/stdc++.h>

using i64 = long long;

const int LIMIT = 2000000;
const int MAXN = 2010;

i64 n;
i64 m;

i64 calc(i64 m) {
    if(m & 1) return m * (m - 1) / 2 + 1;
    else return m * m / 2;
}

int result[LIMIT];

bool mat[MAXN][MAXN];
int next[MAXN];

int main() {
    /*for(int i = 1; i <= 10; ++i)
        std::cout << i << ' ' << calc(i) << std::endl;*/
    std::scanf("%lld", &n);
    /*while(~std::scanf("%lld", &n))*/ {
        i64 l = 1, r = 2e9;
        while(l < r) {
            i64 mid = (l + r) / 2;
            if(calc(mid) <= n) l = mid + 1;
            else r = mid;
        }
        m = l - 1;
        std::printf("%lld\n", m);
        if(n <= LIMIT) {
            int p = 0;
            if(m & 1) {
                for(int i = 0; i < m; ++i)
                    next[i] = m - 1;
                for(int i = 0; i < m; ++i)
                    for(int j = 0; j < m; ++j)
                        mat[i][j] = false;
                int x = 0;
                result[p++] = x;
                while(true) {
                    while(next[x] >= 0 && (next[x] == x || mat[x][next[x]])) --next[x];
                    if(next[x] < 0) break;
                    mat[x][next[x]] = mat[next[x]][x] = true;
                    x = next[x];
                    result[p++] = x;
                }
            } else {
                int x = 0;
                result[p++] = x;
                for(int i = 0; i < m / 2; ++i) {
                    for(int j = 1; j < m; ++j)
                        x = (x + j) % m, result[p++] = x;
                    if(i != m / 2 - 1) x = (x + m / 2 + 1) % m, result[p++] = x;
                }
            }
            while(p < n) result[p++] = 0;
            for(int i = 0; i < n; ++i)
                std::printf("%d%c", result[i] + 1, " \n"[i == n - 1]);
            /*for(int i = 0; i < m; ++i)
                for(int j = 0; j < m; ++j)
                    mat[i][j] = false;
            for(int i = 0; i < n - 1; ++i)
                if(result[i] != result[i + 1]) mat[result[i]][result[i + 1]] = mat[result[i + 1]][result[i]] = true;
            for(int i = 0; i < m - 1; ++i)
                for(int j = i + 1; j < m; ++j)
                    if(!mat[i][j]) { std::cout << "Error " << i + 1 << ' ' << j + 1 << std::endl; return 1; }*/
        }
    }
}
