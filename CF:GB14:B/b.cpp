#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int N;
int p[303];
int a[303];
int vis[303];
vector<vector<int> > adj;
vector<int> val;
vector<int> pos;

void dfs(int u){
	vis[u] = 1;
	pos.push_back(u);
	val.push_back(p[u]);
	for(int i=0;i<adj[u].size();++i){
		int v = adj[u][i];
		if(vis[v])continue;
		dfs(v);
	}
}

int main(){
	int u;
	scanf("%d", &N);
	for(int i=0;i<N;++i){
		scanf("%d", &p[i]);
	}
	adj = vector<vector<int> > (N+3);
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			scanf("%1d", &u);
			if(u) adj[i].push_back(j);
		}
	}
	for(int i=0;i<N;++i){
		if(vis[i])continue;
		val.clear();
		pos.clear();
		dfs(i);
		sort(val.begin(), val.end());
		sort(pos.begin(), pos.end());
		for(int i=0;i<val.size();++i){
			a[pos[i]] = val[i];
		}
	}
	for(int i=0;i<N;++i){
		if(i!=0)printf(" ");
		printf("%d", a[i]);
	}
	printf("\n");
	return 0;
}