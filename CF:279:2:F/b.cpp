#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

//ACCEPTED

int dp[6003][6003]; //dp(u,v) = number of concerts ending with edge u,v
vector<vector<int> > adj;
int val[6003];
int N;

int dfs(int,int,int);
int compute(int,int);

int dfs(int v, int w, int u){
    int ret = (val[v] > val[w] ? 1 : 0);
    if(val[v] > val[u]){
        ret = max(ret, compute(w,u));
    }
    int x;
    for(int i=0;i<adj[w].size();++i){
        x = adj[w][i];
        if(x == u) continue;
        ret = max(ret, dfs(v, x, w));
    }
    return ret;
}

int compute(int u, int v){
    if(dp[u][v] != -1) return dp[u][v];
    int ret = 1;
    int w;
    for(int i=0;i<adj[u].size();++i){
        w = adj[u][i];
        if(w == v) continue;
        ret = max(ret, dfs(v, w, u) + 1);
    }
    if(adj[u].size() == 1 && val[v] > val[u]) ret = 2;
    dp[u][v] = ret;
    return ret;
}

void solve(){
    int ans = 0;
    for(int i=0;i<=N;++i){
        for(int j=0;j<=N;++j){
            dp[i][j] = -1;
        }
    }
    for(int i=1;i<=N;++i){
        for(int j=0;j<adj[i].size();++j){
            ans = max(ans, compute(i, adj[i][j]));
            //printf("(%d,%d)=%d %d\n", i, adj[i][j], compute(i,adj[i][j]), ans);
        }
    }
    printf("%d\n", ans);
}

int main(){
    int u,v;
    scanf("%d", &N);
    for(int i=1;i<=N;++i){
        scanf("%d", &val[i]);
    }
    adj = vector<vector<int> > (N+3);
    for(int i=1;i<N;++i){
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    solve();
}