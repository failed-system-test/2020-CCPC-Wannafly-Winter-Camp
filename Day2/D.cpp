#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <local_debug.hpp>
#else
#define debug(...)
#endif

const int maxn = 1 << 20;
bool have[maxn];

struct SAM {
    int ch[maxn << 1][26], len[maxn << 1] = {-1}, fa[maxn << 1];
    int sz = 2, last = 1;
    void init() {
        sz = 2;
        last = 1;
        memset(ch[1], 0, sizeof(ch[1]));
    }
    void extend(int c) {
        int p = last, np = last = sz++;
        memset(ch[np], 0, sizeof(ch[np]));
        len[np] = len[p] + 1;
        for (; p && !ch[p][c]; p = fa[p]) ch[p][c] = np;
        if (!p) {
            fa[np] = 1;
            return;
        }
        int q = ch[p][c];
        if (len[p] + 1 == len[q]) {
            fa[np] = q;
        } else {
            int nq = sz++;
            len[nq] = len[p] + 1;
            memcpy(ch[nq], ch[q], sizeof(ch[0]));
            fa[nq] = fa[q];
            fa[np] = fa[q] = nq;
            for (; ch[p][c] == q; p = fa[p]) ch[p][c] = nq;
        }
        return;
    }
} sam;

char s[maxn];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        sam.init();
        scanf("%s", s);
        int n = std::strlen(s);
        int mex = -1;
        bool same = true;
        for (int i = 0, ans; i < n; i++) {
            sam.extend(s[i] - 'a');
            same &= (s[i] == s[0]);
            if (!same && sam.len[sam.fa[sam.last]] > mex) {
                mex++;
            } else if (same) {
                mex++;
            }
            ans = same ? 0 : mex + 1;
            printf("%d%c", ans, " \n"[i == n - 1]);
        }
    }
}
