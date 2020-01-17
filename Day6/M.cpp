#include <bits/stdc++.h>

using i64 = long long;

const int MAXN = 110;
const int MAXM = 20;
const int MAXW = 5100;

int n, m, w;

std::vector<bool> submissions[MAXN][MAXM];
bool accepted[MAXN][MAXM];
int submissionCount[MAXN];
int acceptedCount[MAXN];
int problemAccepted[MAXM];

int main() {
    std::scanf("%d%d%d", &n, &m, &w);
    for(int i = 0; i < w; ++i) {
        int x, y, c;
        std::scanf("%d%d%d", &x, &y, &c);
        --x, --y;
        submissions[x][y].push_back(c);
        accepted[x][y] |= c;
    }
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < m; ++j) {
            submissionCount[i] += submissions[i][j].size();
            acceptedCount[i] += accepted[i][j];
        }
    for(int i = 0; i < m; ++i)
        for(int j = 0; j < n; ++j)
            for(auto&& x : submissions[j][i])
                if(x) { ++problemAccepted[i]; break; }
    for(int i = 0; i < n; ++i) {
        i64 result = 0;
        if(!submissionCount[i]) result = 998244353;
        else if(!acceptedCount[i]) result = 1000000;
        else if(acceptedCount[i] == m) result = 0;
        else {
            for(int j = 0; j < m; ++j) {
                if(!accepted[i][j] && problemAccepted[j]) result += 20;
                if(!accepted[i][j] && problemAccepted[j] >= n / 2) result += 10;
                int mk = 0;
                int cur = 0;
                for(int k = 0; k < int(submissions[i][j].size()); ++k) {
                    if(submissions[i][j][k]) mk = std::max(mk, cur), cur = 0;
                    else ++cur;
                }
                mk = std::max(mk, cur);
                result += mk * mk;
                if(!accepted[i][j]) result += mk * mk;
            }
        }
        std::printf("%lld\n", result);
    }
}
