#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <local_debug.hpp>
#else
#define debug(...)
#endif

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i += 2) printf("%d ", i);
    if (n & 1) n--;
    for (int i = n; i > 0; i -= 2) printf("%d ", i);
}
