#include <bits/stdc++.h>

int n;

int main() {
    std::scanf("%d", &n);
    std::printf("%d\n", n);
    for(int i = 0; i < n - 1; ++i)
        std::printf("%d %d\n", -(i + 1), i + 2);
    std::printf("%d %d\n", -n, -n);
}
