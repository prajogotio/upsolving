#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

/* 
Lemma: if u is the node such that max{d(u,v)} is minimum,
then u is on the longest path 
And u must be the one on the middle.
*/

int N,M,Q;
vector<vector<int> > adj;
int par[300005];
int val[300005][2];
int dp[300005];
int len[300005];
int vis[300005];
int rad;

int get_par(int i){
	return (par[i] == i ? i : (par[i] = get_par(par[i])));
}

void merge_set(int u, int v){
	int x = get_par(u);
	int y = get_par(v);
	if(x==y)return;
	int r = max(val[x][0],val[x][1]) + max(val[y][0],val[y][1]) + 1;
	r = max(r, val[x][0]+val[x][1]);
	r = max(r, val[y][0]+val[y][1]);
	val[y][0] = r/2;
	val[y][1] = r - r/2;
	par[x] = y;
}

void dfs(int u, int depth){
	vis[u] = 1;
	len[u] = 0;
	vector<int> tmp;
	for(int i=0;i<adj[u].size();++i){
		int v = adj[u][i];
		if(vis[v])continue;
		dfs(v,depth+1);
		len[u] = max(len[u], len[v]+1);
		tmp.push_back(len[v]);
		rad = max(rad, depth+1+len[v]);
	}
	sort(tmp.begin(),tmp.end());
	if(tmp.size()>1){
		rad = max(rad, 2 + tmp[tmp.size()-1] + tmp[tmp.size()-2]);
	}
}

int main(){
	int u,v,w;
	scanf("%d%d%d", &N,&M,&Q);
	adj = vector<vector<int> > (N+3);
	for(int i=1;i<=N;++i)par[i]=i;
	for(int i=0;i<M;++i){
		scanf("%d%d",&u,&v);
		merge_set(u,v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for(int i=1;i<=N;++i){
		if(vis[i])continue;
		rad = 0;
		dfs(i, 0);
		v = get_par(i);
		val[v][0] = rad/2;
		val[v][1] = rad - rad/2;
	}
	for(int qq=0;qq<Q;++qq){
		scanf("%d", &w);
		if(w==1){
			scanf("%d",&u);
			int x = get_par(u);
			printf("%d\n",val[x][0]+val[x][1]);
		} else {
			scanf("%d%d",&u,&v);
			merge_set(u,v);
		}
	}
	return 0;
}