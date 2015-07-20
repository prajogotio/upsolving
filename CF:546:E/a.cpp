#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <utility>
using namespace std;

int cap[300][300];
int flow[300][300];
vector<vector<int> > adj;
int s, t;
const int inf = 12345678;
int n;
int vis[300];
int par[300];

int pushflow(int v, int mf) {
	//printf("%d ",v);
	if(v == s) {
		return mf;
	}
	int u = par[v];
	if(cap[u][v]<=0) {
		mf = min(mf, flow[v][u]);
	} else {
		mf = min(mf, cap[u][v] - flow[u][v]);
	}
	mf = pushflow(u, mf);
	if(cap[u][v]<=0){
		flow[v][u] -= mf;
	} else {
		flow[u][v] += mf;
	}
	return mf;
}

int bfs() {
	int maxflow = 0;
	while(1){
		for(int i=0;i<2*n;++i) vis[i] = 0;
		vis[t] = 0;
		queue<int> q;
		q.push(s);
		vis[s] = 1;
		par[s] = -1;
		bool pushed = false;
		while(!q.empty()){
			int cur = q.front();
			q.pop();
			for(int i = 0;i < adj[cur].size();++i){
				int next = adj[cur][i];
				if(vis[next]) continue;	
				//printf("%d->%d cap[%d] flow[%d] backflow[%d]\n",cur, next, cap[cur][next], flow[cur][next], flow[next][cur]);
				if(cap[cur][next] - flow[cur][next] <= 0
				&& flow[next][cur] <= 0)continue;
				vis[next] = 1;
				q.push(next);
				par[next] = cur;
				if(next == t) {
					maxflow += pushflow(t, inf);
					//printf("maxflow[%d]\n",maxflow);
					pushed = true;
					break;
				}
			}
			if(pushed)break;
		}
		if(!pushed)break;
	}
	return maxflow;
}

int main(){
	int m, u, v;
	scanf("%d%d",&n,&m);
	s = 2*n;
	t = 2*n+1;
	adj = vector<vector<int> > (2*n+10);
	int sum = 0;
	for(int i=0;i<n;++i){
		scanf("%d",&u);
		cap[s][i] = u;
		sum += u;
		adj[s].push_back(i);
		adj[i].push_back(s);
	}
	int check = 0;
	for(int i=0;i<n;++i){
		scanf("%d",&u);
		cap[i+n][t] = u;
		check += u;
		adj[i+n].push_back(t);
		adj[t].push_back(i+n);
	}
	if(sum != check) {
		printf("NO\n");
		return 0;
	}
	for(int i=0;i<n;++i){
		cap[i][i+n] = inf;
		adj[i].push_back(i+n);
		adj[i+n].push_back(i);
	}
	for(int i=0;i<m;++i){
		scanf("%d%d",&u,&v);
		u--; v--;
		cap[u][v+n] = inf;
		cap[v][u+n] = inf;
		adj[u].push_back(v+n);
		adj[v+n].push_back(u);
		adj[v].push_back(u+n);
		adj[u+n].push_back(v);
	}
	check = bfs();
	if(check == sum) {
		printf("YES\n");
		for(int i=0;i<n;++i){
			for(int j=0;j<n;++j){
				printf("%d ", flow[i][j+n]);
			}
			printf("\n");
		}
	} else {
		printf("NO\n");
	}
	return 0;
}