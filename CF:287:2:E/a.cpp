#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <queue>
#include <vector>
#include <cassert>
using namespace std;

// WRONG IDEA

long long INF = (long long) 1e18;

long long dist[100005];
int par[100005];
int path[100005];
int edges[100005][2];
int ok[100005];
long long weight[100005];
int mark[100005];
vector<vector<pair<long long,int> > > adj;
int N, M;
int S = 1, T;
void dijkstra() {
	priority_queue<pair<long long,pair<int,int> > > pq;
	for(int i=0;i<=N;++i){
		par[i] = -1;
		dist[i] = INF;
	}
	dist[S] = 0;
	pq.push(make_pair(0, make_pair(0, S)));
	while(!pq.empty()){
		int u = pq.top().second.second;
		long long depth = pq.top().second.first;
		long long d = -pq.top().first;
		pq.pop();
		if(u == T) return;
		if(d != dist[u]) continue;
		for(int i=0;i<adj[u].size();++i){
			int v = adj[u][i].first;
			long long w = weight[adj[u][i].second];
			if(w + d + 1LL * 100001 * depth < dist[v]) {
				dist[v] = w+d+1LL*100001*depth;
				pq.push(make_pair(-dist[v], make_pair(depth+1, v)));
				par[v] = u;
				path[v] = adj[u][i].second;
			}
		}
	}
}

int main(){
	int x,y,z;
	scanf("%d%d",&N,&M);
	T=N;
	adj = vector<vector<pair<long long,int> > > (N+3);
	for(int i=0;i<M;++i){
		scanf("%d%d%d",&x,&y,&z);
		adj[x].push_back(make_pair(y, i));
		adj[y].push_back(make_pair(x, i));
		edges[i][0] = x;
		edges[i][1] = y;
		ok[i] = z;
		weight[i] = (ok[i] ? 0 : 1);
	}
	dijkstra();
	int cur = T;
	vector<pair<pair<int,int>,int> > st;
	while(cur != 1) {
		assert(cur != -1);
		mark[path[cur]] = 1;
		if(ok[path[cur]] == 0) {
			st.push_back(make_pair(make_pair(edges[path[cur]][0], edges[path[cur]][1]), 1));
		}
		cur = par[cur];
	}
	for(int i=0;i<M;++i){
		if(mark[i])continue;
		if(ok[i]) st.push_back(make_pair(make_pair(edges[i][0], edges[i][1]),0));
	}
	printf("%d\n",(int)st.size());
	for(int i=0;i<st.size();++i){
		printf("%d %d %d\n", st[i].first.first, st[i].first.second, st[i].second);
	}
	return 0;
}