#include <bits/stdc++.h>

using i64 = long long;

const int MAXN = 1 << 20;
char s[MAXN];
double sum1[MAXN], sum2[MAXN];

std::string x = "aeiouy";

int main() {

    scanf("%s", s);

    int n = std::strlen(s);

    /*double xx = 0;
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            for(int k = i; k <= j; ++k)
                if (~x.find(s[k]))
                    xx += 1.0 / (j - i + 1);
    std::printf("%.10f\n", xx / (i64(n) * (n + 1) / 2));*/

    sum1[0] = 0;
    for(int i = 1; i <= n; ++i)
        sum1[i] = sum1[i - 1] + 1.0 / i;
    sum2[0] = 0;
    for(int i = 1; i <= n; ++i)
        sum2[i] = sum2[i - 1] + double(n - i + 1) / i;

    double result = 0;
    for (int i = 0; i < n; i++)
        if (~x.find(s[i])) {
            int x = std::min(i + 1, n - i);
            int y = n - x + 1;
            result += x * (1 + sum1[y] - sum1[x]) + (sum2[n] - sum2[y]);
        }
    std::printf("%.10f\n", result / (i64(n) * (n + 1) / 2));

}