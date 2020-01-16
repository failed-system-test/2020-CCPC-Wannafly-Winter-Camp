#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
int a[3][maxn], m[3];
map<int,int> cnt;

int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=0;i<k;i++){
        scanf("%d",m+i);
        for(int j=0;j<m[i];j++) scanf("%d",&a[i][j]), cnt[a[i][j]]++;
    }
    int tot2 = 0, tot3 = 0;
    for(auto &V:cnt){
        if(V.second == 2) tot2++;
        else if(V.second == 3) tot3++;
    }

    int ans = 0;
    for(int i=0;i<k;i++){
        int c1 = 0, c2 = 0;
        for(int j=0;j<m[i];j++){
            if(cnt[a[i][j]] == 1) c1++;
            else if(cnt[a[i][j]] == 2) c2++;
        }
        int tmp = tot3 + c2 + max((tot2 - c2), c1); 
        ans = max(ans, tmp);
    }
    printf("%d\n",ans);
}