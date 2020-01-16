#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <local_debug.hpp>
#else
#define debug(...)
#endif

const int MAXN = 64;
char s[MAXN][MAXN];

template<int T>
class Base {
   private:
    std::bitset<T> basis[T];

   public:
    void insert(std::bitset<T> x) {
        for (int i = T - 1; ~i; i--) {
            if (x[i]) {
                if (basis[i].none()) {
                    basis[i] = x;
                    return;
                }
                x ^= basis[i];
            }
        }
    }
    int rank() {
        int res = 0;
        for (int i = 0; i < T; i++) {
            if (!basis[i].none()) {
                res++;
            }
        }
        return res;
    }
    
};

Base<1024> base;

const int mod = 1e9 + 7;

int main() {
    int k;
    scanf("%d", &k);
    for (int i = 0; i < (1 << k); i++) {
        scanf("%s", s[i]);
    }
    int n = 1 << k;
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j) {
            std::bitset<1024> b;
            for(int ii = 0; ii < n; ++ii)
                for(int jj = 0; jj < n; ++jj)
                    b[ii * n + jj] = s[(i + ii) % n][(j + jj) % n] == '1';
            base.insert(b);
        }
    int res = base.rank();
    int ans = 1;
    for (int i = 0; i < res; i++) {
        ans <<= 1;
        if (ans >= mod) ans -= mod;
    }
    printf("%d\n", ans);
}
