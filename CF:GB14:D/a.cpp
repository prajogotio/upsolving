#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cstring>
#include <utility>
using namespace std;

/* LINEARITY OF EXPECTATION */

vector<vector<int> > adj;
pair<int,int> edge[100005];
int vis[100005];
int len[100005];
int sz[100005];
double prob[100005];
int N, M;

void dfs(int u){
	vis[u] = 1;
	sz[u] = 1;
	for(int i=0;i<adj[u].size();++i){
		int v = adj[u][i];
		if(vis[v]) continue;
		dfs(v);
		sz[u] += sz[v];
	}
}

int main(){
	int u, v, w;
	scanf("%d", &N);
	adj = vector<vector<int> >(N+3);
	for(int i=1;i<N;++i){
		scanf("%d%d%d", &u,&v,&w);
		edge[i] = make_pair(u,v);
		len[i] = w;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for(int i=1;i<=N;++i){
		if(adj[i].size()==1){
			dfs(i);
			break;
		}
	}
	double E = 0;
	double q = 1.00 * N * (N-1) * (N-2);
	for(int i=1;i<N;++i){
		int k = min(sz[edge[i].first], sz[edge[i].second]);
		int _k = N-k;
		if(k >= 3){
			prob[i] += 1.00 * k * (k-1) * (k-2);
		}
		if(_k >= 3){
			prob[i] += 1.00 * _k * (_k-1) * (_k-2);
		}
		prob[i] = 1.0 - prob[i]/q;
		E += prob[i] * len[i];
	}
	scanf("%d", &M);
	for(int i=0;i<M;++i){
		scanf("%d%d", &u,&w);
		E -= prob[u] * (len[u] - w);
		printf("%.12lf\n", 2.0 * E);
		len[u] = w;
	}
	return 0;
}