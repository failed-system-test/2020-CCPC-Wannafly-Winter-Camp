#include <bits/stdc++.h>

using i64 = long long;

const int MAXN = 101000;

i64 gcd(i64 a, i64 b) { return a ? gcd(b % a, a) : b; }

int t, n, l;

int main() {
    std::scanf("%d", &t);
    std::vector<int> result;
    result.reserve(4 * MAXN);
    for(int test = 0; test < t; ++test) {
        std::scanf("%d%d", &n, &l);
        result.clear();
        switch(l) {
        case 1: result = {1, 1, 1, 1}; break;
        case 2: result = {1, 1, 2, 2}; break;
        case 3: result = {1, 1, 2, 2, 2, 3, 3}; break;
        case 4: result = {1, 1, 1, 2, 3, 3, 3}; break;
        case 5: result = {2, 2, 2, 3, 4, 4, 4}; break;
        case 6: result = {2, 2, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6}; break;
        default: {
            switch(l % 3) {
            case 0: {
                for(int i = 2; i <= l - 3; ++i)
                    result.push_back(i), result.push_back(i);
                for(int i = l - 2; i <= l; ++i)
                    result.push_back(i), result.push_back(i), result.push_back(i);
                break;
            }
            case 1: {
                result.push_back(1);
                result.push_back(1);
                result.push_back(1);
                for(int i = 2; i <= l - 2; ++i)
                    result.push_back(i);
                result.push_back(l - 1);
                result.push_back(l - 1);
                result.push_back(l - 1);
                break;
            }
            case 2: {
                result.push_back(2);
                result.push_back(2);
                result.push_back(2);
                for(int i = 3; i <= l - 2; ++i)
                    result.push_back(i);
                result.push_back(l - 1);
                result.push_back(l - 1);
                result.push_back(l - 1);
                break;
            }
            }
            break;
        }
        }
        int m = result.size();
        assert(m % 3 == 1);
        std::printf("%d\n", m / 3);
        for(int i = 0; i < m; ++i)
            std::printf("%d%c", result[i], " \n"[i == m - 1]);
    }
}