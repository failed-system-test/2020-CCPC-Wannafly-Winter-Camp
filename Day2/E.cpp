#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <local_debug.hpp>
#else
#define debug(...)
#endif
using namespace std;
using ll = long long;
const int maxn = 1e5+5;
vector<int> G[maxn];
bool bigc[maxn];
int sz[maxn];
set<int> id;
ll ans[maxn], tot;

int szdfs(int u){
    sz[u] = 1;
    for(auto &v:G[u])
        sz[u] += szdfs(v);
    return sz[u];
}

inline ll squ(ll x){
    return x * x;
}
void add(int u){
    if(!id.empty()){
        auto nxt = id.upper_bound(u);
        if(nxt == id.end()){
            auto x = *(--nxt);
            tot += squ(x - u);
        } else if(nxt == id.begin()){
            auto x = *nxt;
            tot += squ(x - u);
        } else {
            auto y = *nxt, x = *(--nxt);
            tot += squ(x - u) + squ(y - u) - squ(x - y); 
        }
    }
    id.insert(u);
    for(auto &v:G[u])
        if(!bigc[v]) add(v);
}
void del(int u){
    id.erase(u);
    if(!id.empty()){
        auto nxt = id.upper_bound(u);
        if(nxt == id.end()){
            auto x = *(--nxt);
            tot -= squ(x - u);
        } else if(nxt == id.begin()){
            auto x = *nxt;
            tot -= squ(x - u);
        } else {
            auto y = *nxt, x = *(--nxt);
            tot -= squ(x - u) + squ(y - u) - squ(x - y); 
        }
    }
    for(auto &v:G[u])
        if(!bigc[v]) del(v);
}

void dfs(int u, bool keep){
    int mx = -1, bc = -1;
    for(auto &v:G[u]){
        if(sz[v] > mx){
            mx = sz[v];
            bc = v;
        }
    }
    for(auto &v:G[u])
        if(v != bc) dfs(v, 0);
    if(bc != -1){
        dfs(bc, 1);
        bigc[bc] = 1;
    }
    add(u);
    ans[u] = tot;
    if(bc != -1) bigc[bc] = 0;
    if(!keep) del(u);
}

int main() {
    int n;
    scanf("%d",&n);
    for(int i=2,p;i<=n;i++){
        scanf("%d",&p);
        G[p].push_back(i);
    }    
    tot = 0;
    szdfs(1);
    dfs(1,1);
    for(int i=1;i<=n;i++)
        printf("%lld\n", ans[i]);
}