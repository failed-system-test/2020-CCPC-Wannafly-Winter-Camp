#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <local_debug.hpp>
#else
#define debug(...)
#endif
using namespace std;

using ll = long long;
using pii = pair<ll,ll>;
const int maxn =  1e4+6;
const int mod = 998244353;
pii a[maxn];
ll length[maxn], invLen[maxn];
int id[maxn];

ll Pow(ll a,ll b){
    ll ret = 1;
    while(b){
        if(b & 1) ret = ret * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ret;
}
ll inv(ll x){
    return Pow(x, mod-2);
}
pii cal(int l,int r){
    ll a1 = a[l].first, a2 = a[l].second;
    ll b1 = a[r].first, b2 = a[r].second;
    ll x = length[l];
    ll y = length[r];
    if(a1 > b2) return {x * y, 0};
    if(b1 > a2) return {0, x * y};
    ll tot = x * y - max(0LL, min(a2,b2) - max(a1,b1) + 1);
    ll L = max(min(a1,b2) - b1, 0LL);
    ll R = max(0LL, min(a2,b2) - b1);
    ll len = R - L + 1;
    ll t1 = max(a2- max(b2, a1), 0LL) * y + (L + R) * len / 2;
    ll t2 = tot - t1;
    return {t1, t2};
}
int main() {
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%lld%lld",&a[i].first, &a[i].second), id[i] = i, length[i] = a[i].second - a[i].first + 1, invLen[i] = inv(length[i]);
    // cerr << "before" << endl;
    sort(id, id+n, [&](int l,int r){
        return a[l].first + a[l].second < a[r].first + a[r].second;
        //pii tmp = cal(l, r);
        //return tmp.first < tmp.second;
    });
    // cerr << "after" << endl;
    ll sum = 1, ans = 0;
    for(int i=0;i<n;i++) sum = sum * length[i] % mod;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            int d1 = id[i], d2 = id[j];
            ll tmpsum = sum * invLen[d1] % mod * invLen[d2] % mod;
            pii val = cal(d1, d2);
            ans = (ans + val.first % mod * tmpsum % mod) % mod;
        }
    }
    printf("%lld\n", ans * inv(sum) % mod);
}
