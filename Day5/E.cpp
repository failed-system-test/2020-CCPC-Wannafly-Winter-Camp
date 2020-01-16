#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <local_debug.hpp>
#else
#define debug(...)
#endif

const int MAXN = 305;
int a[MAXN], b[4];

int suf[MAXN][MAXN];

inline bool check(int index[3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((b[i] == b[j]) ^ (a[index[i]] == a[index[j]])) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", a + i);
    }
    for (int i = 0; i < 4; i++) {
        scanf("%d", b + i);
    }
    for (int i = n - 1; ~i; i--) {
        memcpy(suf[i], suf[i + 1], sizeof(suf[i + 1]));
        suf[i][a[i]]++;
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                int index[] = {i, j, k};

                if (check(index)) {
                    for (int c = 0; c < 3; c++) {
                        if (b[3] == b[c]) {
                            ans += suf[k + 1][a[index[c]]];
                            break;
                        }
                    }
                    if (b[3] != b[0] && b[3] != b[1] && b[3] != b[2]) {
                        int vec[3] = {a[i], a[j], a[k]};
                        std::sort(vec, vec + 3);
                        int cc = std::unique(vec, vec + 3) - vec;
                        ans += n - k - 1;
                        for(int l = 0; l < cc; ++l)
                            ans -= suf[k + 1][vec[l]];
                    }
                }
            }
        }
    }
    printf("%lld\n", ans);
}
