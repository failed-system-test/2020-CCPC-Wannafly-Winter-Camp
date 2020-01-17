#include <bits/stdc++.h>

using i64 = long long;

const int MAXN = 1100;

int t, n, a, b, c, d;
char poison[MAXN];

int solveBest() {
    std::vector<std::pair<int, int>> vec = {{a, b}, {c, d}};
    int result = 0;
    for(int i = 0; i < n; ++i) {
        while(!vec.empty() && !vec.back().first && !vec.back().second) vec.pop_back();
        if(vec.empty()) break;
        if(poison[i] == '1') {
            if(vec.back().first) --vec.back().first, ++result;
            else --vec.back().second, ++vec.back().first;
        } else {
            if(vec.back().second) --vec.back().second, ++vec.back().first;
        }
    }
    return result;
}
int solveWorst() {
    std::vector<std::pair<int, int>> vec = {{a, b}, {c, d}};
    int result = 0;
    for(int i = 0; i < n; ++i) {
        while(!vec.empty() && !vec.back().first && !vec.back().second) vec.pop_back();
        if(vec.empty()) break;
        if(poison[i] == '1') {
            if(vec.back().second) --vec.back().second, ++vec.back().first;
            else --vec.back().first, ++result;
        } else {
            if(!vec.back().first) --vec.back().second, ++vec.back().first;
        }
    }
    return result;
}

int main() {
    std::scanf("%d", &t);
    for(int test = 0; test < t; ++test) {
        std::scanf("%d%d%d%d%d%s", &n, &a, &b, &c, &d, poison);
        std::printf("%d %d\n", solveBest(), solveWorst());
    }
}
