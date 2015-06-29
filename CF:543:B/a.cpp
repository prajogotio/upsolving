#include <algorithm>
#include <vector>
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;

namespace cf {
int n, m;
int s1, t1, s2, t2, l1, l2;
vector<vector<int> > adj;
int dist[3010][3010];

void bfs(int src) {
	queue<int> q;
	dist[src][src] = 0;
	q.push(src);
	while(!q.empty()){
		int u = q.front();
		q.pop();
		for(int i=0;i<adj[u].size();++i){
			int v = adj[u][i];
			if (dist[src][v] != -1) continue;
			dist[src][v] = dist[src][u]+1;
			q.push(v);
		}
	}
}

bool check(int s, int u, int v, int t, int l) {
	return dist[s][u] + dist[u][v] + dist[v][t] <= l;
}

void solve() {
	scanf("%d%d",&n,&m);
	adj = vector<vector<int> >(n+10);
	int u,v;
	for(int i=0;i<=n;++i){
		for(int j=0;j<=n;++j){
			dist[i][j] = -1;
		}
	}
	for(int i=0;i<m;++i){
		scanf("%d%d",&u,&v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	scanf("%d%d%d%d%d%d",&s1,&t1,&l1,&s2,&t2,&l2);
	for(int i=1;i<=n;++i){
		bfs(i);
	}
	if (dist[s1][t1] > l1 || dist[s2][t2] > l2) {
		printf("-1\n");
		return;
	}
	int ans = m - dist[s1][t1] - dist[s2][t2];
	for(int u=1;u<=n;++u){
		for(int v=1;v<=n;++v){
			if( check(s1,u,v,t1,l1) && check(s2,u,v,t2,l2)) {
				ans = max(ans, m-dist[s1][u]-dist[s2][u]-dist[t1][v]-dist[t2][v]-dist[u][v]);
			}
			if(check(s1,u,v,t1,l1) && check(s2,v,u,t2,l2)) {
				ans = max(ans, m-dist[s1][u]-dist[s2][v]-dist[t1][v]-dist[t2][u]-dist[u][v]);
			}
		}
	}
	printf("%d\n",ans);
}

}


int main(){
	cf::solve();
	return 0;
}