#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cassert>
using namespace std;
int mark[2000005];
int ins[2000005];
vector<int> prime;
int N, Q;
int a[100005];
vector<vector<int> > factor;
int dp[100005];
int r[100005];
int done[2000005];
int vis[100005];
vector<vector<int> > adj;
void dfs(int u, int p, int prev){
	vis[u] = 1;
	if(a[u]%p == 0) {
		if(dp[u] == -1 || (prev != -1 && r[prev] > r[dp[u]])) dp[u] = prev;
		if(prev == -1 || r[prev] < r[u]) prev = u;
	}
	for(int i=0;i<adj[u].size();++i){
		int v = adj[u][i];
		if(vis[v]) continue;
		r[v] = r[u] + 1;
		dfs(v,p,prev);
		for(int j=0;j<factor[v].size();++j){
			if(done[factor[v][j]])continue;
			done[factor[v][j]] = 1;
			dfs(v,factor[v][j],-1);
			done[factor[v][j]] = 0;
		}
	}
	vis[u] = 0;
}

void build(){
	memset(dp, -1, sizeof dp);
	memset(vis, 0, sizeof vis);
	r[1] = 1;
	for(int k=0;k<factor[1].size();++k){
		done[factor[1][k]] = 1;
		dfs(1,factor[1][k],-1);
		done[factor[1][k]] = 0;
	}
}

void factorize(int k){
	factor[k].clear();
	if(!mark[a[k]]) {
		factor[k].push_back(a[k]);
		return;
	}
	for(int i=0;i<prime.size();++i){
		if(a[k]%prime[i]==0)factor[k].push_back(prime[i]);
	}	
}

int main(){
	int type,u, v;
	mark[0] = mark[1] = 1;
	for(int i=2;i*i<=2000000;++i){
		for(int j=i;j*i<=2000000;++j){
			mark[i*j] = 1;
		}
	}
	for(int i=2;i<=1415;++i){
		if(!mark[i])prime.push_back(i);
	}
	scanf("%d %d", &N, &Q);
	adj = vector<vector<int> > (N+3);
	factor = vector<vector<int> > (N+3);
	for(int i=1;i<=N;++i){
		scanf("%d", &a[i]);
		factorize(i);
	}
	for(int i=1;i<=N-1;++i){
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	build();
	for(int qq=0;qq<Q;++qq){
		scanf("%d", &type);
		if(type == 1){
			scanf("%d", &v);
			printf("%d\n", dp[v]);
		} else {
			scanf("%d %d", &u, &v);
			a[u] = v;
			factorize(u);
			build();
		}
	}
	return 0;
}