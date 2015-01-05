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
int idx[2000005];
int vis[100005];
vector<vector<int> > adj;
void dfs(int u){
	vis[u] = 1;
	vector<int> tmp;
	for(int i=0;i<factor[u].size();++i){
		int f = factor[u][i];
		tmp.push_back(idx[f]);
		if(dp[u] == -1 || (idx[f] != -1 && r[idx[f]] > r[dp[u]])) dp[u] = idx[f];
		idx[f] = u;
	}
	for(int i=0;i<adj[u].size();++i){
		int v = adj[u][i];
		if(vis[v])continue;
		r[v] = r[u]+1;
		dfs(v);
	}
	for(int i=0;i<factor[u].size();++i){
		idx[factor[u][i]] = tmp[i];
	}
	vis[u] = 0;
}

void build(){
	memset(dp, -1, sizeof dp);
	memset(vis, 0, sizeof vis);
	memset(idx, -1, sizeof idx);
	r[1] = 1;
	dfs(1);
}

void factorize(int k){
	factor[k].clear();
	int tmp = a[k];
	for(int i=0;i<prime.size();++i){
		if(a[k]%prime[i]==0)factor[k].push_back(prime[i]);
		while(tmp%prime[i]==0)tmp /= prime[i];
	}	
	if(tmp != 1) factor[k].push_back(tmp);
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