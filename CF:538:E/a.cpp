#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

struct info {
	int size;
	int best;
	int worst;
};

vector<vector<int> > adj;
vector<info> node;
int n;

void dfs(int u, int me) {
	if (adj[u].size() == 0) {
		node[u].size = 1;
		node[u].best = 1;
		node[u].worst = 1;
		return;
	}
	int size = 0;
	for(int i=0;i<adj[u].size();++i){
		int v = adj[u][i];
		dfs(v, me ^ 1);
		size += node[v].size;
	}
	int best = 0;
	int worst = 12345678;
	if (me == 1) {
		worst = 0;
		for(int i=0;i<adj[u].size();++i){
			int v = adj[u][i];
			best = max(best, size - node[v].size + node[v].best);
			worst += node[v].worst;
		}
	} else {
		best = 0;
		for (int i = 0;i < adj[u].size(); ++i){
			int v = adj[u][i];
			best += node[v].best - 1;
			worst = min(worst, node[v].worst);
		}
		best++;
	}
	node[u].size = size;
	node[u].best = best;
	node[u].worst = worst;
}

int main(){
	scanf("%d",&n);
	int u,v;
	adj = vector<vector<int> >(n+3);
	node = vector<info> (n+3);
	for(int i=0;i<n-1;++i){
		scanf("%d%d",&u,&v);
		adj[u].push_back(v);
	}
	dfs(1, 1);
	printf("%d %d\n", node[1].best, node[1].worst);
	return 0;
}