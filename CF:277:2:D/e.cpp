#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
long long MOD = (long long) 1e9 + 7LL;
vector<vector<int> > adj;
int val[2003];
int vis[2003];
int N, D;

long long dfs(int u, int r){
    vis[u] = 1;
    long long ret = 1LL;
    for(int i=0;i<adj[u].size();++i){
        int v = adj[u][i];
        if(vis[v]) continue;
        if(val[v] == val[r] && v < r) continue;
        if(val[r] <= val[v] && val[v] - val[r] <= D){
            ret *= (1LL + dfs(v,r));
            ret %= MOD;
        }
    }
    return ret;
}

int main(){
    int u, v;
    scanf("%d %d", &D, &N);
    for(int i=0;i<N;++i){
        scanf("%d", &val[i]);
    }
    adj = vector<vector<int> > (N+3);
    for(int i=0;i<N-1;++i){
        scanf("%d %d", &u, &v);
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    long long ans = 0LL;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j) vis[j] = 0;
        ans += dfs(i,i);
        ans %= MOD;
    }
    cout << ans << endl;
    return 0;
}