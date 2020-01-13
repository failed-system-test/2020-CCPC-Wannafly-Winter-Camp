#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#include <local_debug.hpp>
#else
#define debug(...)
#endif


using u64 = unsigned long long;
using namespace std;

const int BITS = 60;
const int MAXN = 101000;

struct Node {
    int size;
    int tag;
    int childs[2];
};

int n;
u64 arr[MAXN];

Node nodes[MAXN * BITS];
int ns = 0;

int alloc() {
    nodes[ns] = {0, 0, {-1, -1}};
    return ns++;
}
using pii = std::pair<int,int> ;
std::map<int, std::vector<pii>> vec;

void insert(u64 x, int id) {
    int p = 0;
    int res = 0;
    for (int i = BITS - 1; i >= 0; --i) {
        bool b = (x >> i) & 1;
        if (nodes[p].childs[b] == -1) nodes[p].childs[b] = alloc();
        ++nodes[p].size;
        res += nodes[p].tag;
        if(nodes[p].childs[b ^ 1] != -1) nodes[nodes[p].childs[b^1]].tag += res;
        nodes[p].tag = 0;
        p = nodes[p].childs[b];
    }
    res += nodes[p].tag;
    nodes[p].tag = 0;
    ++nodes[p].size;
    if(vec[p].size()) vec[p].back().second += res;
    vec[p].push_back({id, 0});
}

void query(u64 x) {
    int p = 0;
    for (int i = BITS - 1; i >= 0; --i) {
        bool b = (x >> i) & 1;
        if (b == 1 && nodes[p].childs[1] != -1) {
            nodes[nodes[p].childs[1]].tag++;
        }
        p = nodes[p].childs[0];
        if (p == -1) break;
    }
}

int ans[MAXN];

void dfs(int u, int c = 0, int dep = BITS - 1) {
    if (dep == -1) {
        std::reverse(vec[u].begin(), vec[u].end());
        int last = c + nodes[u].tag;
        // debug(last);
        // debug(vec[u]);

        for (auto& x : vec[u]) {
            ans[x.first] = last + x.second;
            last = ans[x.first];
        }
        return;
    }
    for (int i = 0; i < 2; i++) {
        if (nodes[u].childs[i] != -1) {
            dfs(nodes[u].childs[i], c + nodes[u].tag, dep - 1);
        }
    }
}

u64 sum[MAXN];
// int cnt[MAXN];

int main() {
    // freopen("1.in","r",stdin);
    std::scanf("%d", &n);
    ns = 0;
    alloc();
    for (int i = 0; i < n; ++i) std::scanf("%llu", &arr[i]);
    std::partial_sum(arr, arr + n, sum, std::bit_xor<>());
    for (int i = n - 1; ~i; i--) {
        insert(sum[i], i);
        query(arr[i]);
    }
    dfs(0);
    
    // for(int i=0;i<n;i++){
        // for(int j=0;j<=i;j++){
            // if((arr[j] ^ sum[i]) < arr[j]) cnt[i]++;
        // }
    // }
    for (int i = 0; i < n; i++) {
        printf("%d\n", ans[i]);
        // if(ans[i] != cnt[i]){
            // cerr << "error" << endl;
            // return 0;
        // }
    }

}