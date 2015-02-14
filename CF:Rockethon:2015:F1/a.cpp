#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

// WRONG GRAPH, MUST PUT CONSTRAINT FOR EACH CELL USING IN - OUT DESIGN

int vis[1000], par[1000];
int cap[1000][1000], f[1000][1000];
vector<vector<int> > adj;
int N, M;
int males, females;

// source = 998, sink = 999, 
// 0..Q-1 are male/females, Q..997 are cells
int S = 998, T = 999;
int Q = 500, INF = 1234567;
int maxflow;

int augment_path(int v, int mf){
	if(v == S) {
		return mf;
	}
	bool backedge = false;
	int u = par[v];
	if(cap[u][v] - f[u][v] == 0 && f[v][u] > 0) {
		backedge = true;
	}
	if(backedge){
		mf = min(mf, f[v][u]);
	} else {
		mf = min(mf, cap[u][v] - f[u][v]);
	}
	mf = augment_path(u, mf);
	if(backedge){
		f[v][u] -= mf;
	} else {
		f[u][v] += mf;
	}
	return mf;
}

bool edmondkarps() {
	maxflow = 0;
	while(1){
		queue<int> q;
		bool augmented = false;
		q.push(S);
		for(int i=0,X=males+females;i<X;++i){vis[i]=0;}
		for(int i=Q,X=Q+N*M;i<X;++i){vis[i]=0;}
		vis[T] = 0;
		vis[S] = 1;
		while(!q.empty()){
			int u = q.front();
			q.pop();
			for(int i=0;i<adj[u].size();++i){
				int v = adj[u][i];
				if(vis[v])continue;
				vis[v] = 1;
				if(cap[u][v] - f[u][v] > 0 || f[v][u] > 0) {
					par[v] = u;
					if(v == T) {
						int flow = augment_path(T, INF);
						maxflow += flow;
						augmented = true;
					} else {
						q.push(v);
					}
				}
				if(augmented) break;
			}
			if(augmented) break;
		}
		if(!augmented) break;
	}
	return (maxflow == males);
}

string cells[30];
long long dist[1000][1000];
int bfs[23][23];
long long DINF = (long long) 1e18;

void bfs_next(int x, int y, int d, queue<pair<pair<int,int>,int> > & q) {
	if(x<0 || y<0 || x>=N || y>=M)return;
	if(!bfs[x][y] && cells[x][y] != '#'){
		bfs[x][y] = 1;
		q.push(make_pair(make_pair(x,y),d+1));
	}
}

// 1-based to 0-based
void get_dist(int i, int r, int c, int t) {
	--r; --c;
	queue<pair<pair<int,int>,int> > q;
	for(int j=0;j<N;++j){
		for(int k=0;k<M;++k){
			dist[i][j*M+k+Q]=DINF;
			bfs[j][k] = 0;
		}
	}
	q.push(make_pair(make_pair(r,c),0));
	bfs[r][c] = 1;
	while(!q.empty()){
		pair<pair<int,int>,int> u = q.front();
		int x = u.first.first;
		int y = u.first.second;
		q.pop();
		int d = u.second;
		dist[i][Q+x*M+y] = 1LL*d*t;
		bfs_next(x-1,y,d,q);
		bfs_next(x,y-1,d,q);
		bfs_next(x+1,y,d,q);
		bfs_next(x,y+1,d,q);
	}
}

bool solvable(long long max_dist) {
	adj = vector<vector<int> >(1003);
	for(int i=0;i<males+females;++i){
		f[S][i] = f[i][T] = 0;
		cap[S][i] = cap[i][T] = 0;
		for(int j=Q;j<Q+N*M;++j){
			cap[i][j] = 0;
			f[i][j] = 0;
		}
	}
	for(int i=0;i<males+females;++i){
		if(i < males) {
			adj[S].push_back(i);
			cap[S][i] = 1;
			f[S][i] = 0;
		}
		else {
			adj[i].push_back(T);
			cap[i][T] = 1;
			f[i][T] = 0;
		}
		for(int j=Q;j<Q+N*M;++j){
			if(dist[i][j] <= max_dist) {
				if(i<males){
					cap[i][j] = 1;
					adj[i].push_back(j);
				} else {
					cap[j][i] = 1;
					adj[j].push_back(i);
				}
			}
		}
	}
	
	return edmondkarps();
}

int main(){
	int u,v,w;
	scanf("%d%d%d%d", &N,&M,&males,&females);
	if(males+1 != females && females+1 != males) {
		printf("-1\n"); return 0;
	}
	for(int i=0;i<N;++i){
		cin >> cells[i];
	}
	bool is_male = false;
	if(males < females) {
		is_male = true;
		++males;
	} else {
		++females;
	}
	scanf("%d%d%d",&u,&v,&w);
	if(is_male){
		get_dist(0, u,v,w);
	} else {
		get_dist(males, u,v,w);
	}
	for(int i=(is_male?1:0); i<males;++i){
		scanf("%d%d%d",&u,&v,&w);
		get_dist(i,u,v,w);
	}
	for(int i=(is_male?males:males+1);i<males+females;++i){
		scanf("%d%d%d",&u,&v,&w);
		get_dist(i,u,v,w);
	}
	// long long lo = 0, hi = (long long) 1e13, mid;
	// while(lo<=hi) {
	// 	mid = (lo+hi)/2LL;
	// 	if(solvable(mid)) {
	// 		hi = mid-1;
	// 	} else {
	// 		lo = mid+1;
	// 	}
	// }
	// cout << lo << endl;
	printf("%d\n",solvable(1));
	return 0;
}