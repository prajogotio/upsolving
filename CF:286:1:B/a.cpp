#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

vector<vector<int> > adj, graph;
int N, M;
int vis[100005];
int ff[100005];
int mark[100005];
int color;
int ctr;
vector<int> S;
int low[100005],idx[100005],in_S[100005];
void dfs(int u){
	vis[u] = 1;
	ff[u] = color;
	for(int i=0;i<adj[u].size();++i){
		int v = adj[u][i];
		if(vis[v])continue;
		dfs(v);
	}
}

void scc(int u){
	if(mark[ff[u]])return;
	vis[u] = 1;
	low[u] = ctr;
	idx[u] = ctr;
	ctr++;
	in_S[u] = 1;
	S.push_back(u);
	for(int i=0;i<graph[u].size();++i){
		int v = graph[u][i];
		if(!vis[v]){
			scc(v);
			low[u] = min(low[u], low[v]);
		} else if(in_S[v]){
			low[u] = min(low[u], idx[v]);
		}
		if(mark[ff[u]])return;
	}
	if(low[u] == idx[u]){
		int sz = 0;
		while(!S.empty()){
			int v = S.back();
			S.pop_back();
			++sz;
			in_S[v] = 0;
			if(v == u)break;
		}
		if(sz > 1){
			mark[ff[u]] = 1;
			return;
		}
	}
}

int main(){
	int u,v;
	scanf("%d%d",&N,&M);
	adj = vector<vector<int> > (N+3);
	graph = vector<vector<int> > (N+3);
	for(int i=0;i<M;++i){
		scanf("%d%d",&u,&v);
		adj[u].push_back(v);
		adj[v].push_back(u);
		graph[u].push_back(v);
	}
	int cc = 0;
	color = 1;
	for(int i=1;i<=N;++i){
		if(vis[i])continue;
		dfs(i);
		++cc;
		++color;
	}
	for(int i=1;i<=N;++i)vis[i] = 0;
	ctr = 1;
	for(int i=1;i<=N;++i){
		if(vis[i])continue;
		if(mark[ff[i]])continue;
		scc(i);
		cc -= mark[ff[i]];
	}
	printf("%d\n",N-cc);
	return 0;
}