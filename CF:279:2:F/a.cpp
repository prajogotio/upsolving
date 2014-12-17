#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <set>
using namespace std;


/* TLE, O(N^3lgN) */

vector<vector<int> > adj;
int val[6003];
vector<int> leaves;
//int dp[6003];
set<int> S;
int vis[6003];
int par[6003];
int N;

void dfs(int u){
    vis[u] = 1;
    for(int i=0;i<adj[u].size();++i){
        int v = adj[u][i];
        if(vis[v]) continue;
        par[v] = u;
        dfs(v);
    }
}

int compute(int u, int v){
    int ret = 1;
    //dp[u] = 1;
    for(int i=0;i<=6000;++i){
        vis[i] = 0;
        par[i] = -1;
    }
    dfs(v);
    int cur = u, w;
    S.clear();
    S.insert(val[u]);
    while(1){
        cur = par[cur];
        //dp[cur] = 1;
        /*
        w = u;
        while(w != cur){
            if(val[w] < val[cur]){
                dp[cur] = max(dp[cur], dp[w] + 1);
            }
            w = par[w];
        }
        */
        pair<set<int>::iterator,bool> it = S.insert(val[cur]);
        ++it.first;
        if(it.first != S.end()) S.erase(it.first);
        //ret = max(dp[cur], ret);
        if(cur == v) break;
    }
    ret = S.size();
    return ret;
}

void solve(){
    int ans = 0;
    for(int i=1;i<=N;++i){
        if(adj[i].size()==1){
            leaves.push_back(i);
        }
    }
    for(int i=0;i<leaves.size();++i){
        for(int j=0;j<leaves.size();++j){
            if(leaves[i]==leaves[j]) continue;
            ans = max(ans, compute(leaves[i],leaves[j]));
        }
    }
    printf("%d\n", ans);
}

int main(){
    scanf("%d", &N);
    adj = vector<vector<int> >(N+3);
    for(int i=1;i<=N;++i){
        scanf("%d", &val[i]);
    }
    int u,v;
    for(int i=1;i<N;++i){
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    solve();
    return 0;
}