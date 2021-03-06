#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#include <utility>
#include <string>
using namespace std;

// N,M <= 11
// females+males+in+out = 4 * 11*11 ~= 500

int females, males;
int N,M;
string cell[30];
int cap[500][500], flow[500][500];
int vis[500], par[500];
vector<vector<int> > adj;
int max_flow;
int S=498, T=499, INF=123456;
bool possible;
int augment_path(int v, int mf){
	if(v==S) return mf;
	int u = par[v];
	bool backedge = false;
	if(flow[v][u] > 0){
		backedge = true;
	}
	if(backedge){
		mf = min(mf, flow[v][u]);
	} else {
		mf = min(mf, cap[u][v] - flow[u][v]);
	}
	mf = augment_path(u,mf);
	if(backedge) {
		flow[v][u] -= mf;
	} else {
		flow[u][v] += mf;
	}
	return mf;
}

bool edmondskarp() {
	max_flow = 0;
	while(1) {
		bool augmented = false;
		queue<int> q;
		for(int i=0;i<500;++i){vis[i] = 0;}
		q.push(S);
		vis[S] = 1;
		vis[T] = 0;
		while(!q.empty()){
			int u = q.front();
			q.pop();
			for(int i=0;i<adj[u].size();++i){
				int v = adj[u][i];
				if(vis[v])continue;
				if(cap[u][v]-flow[u][v] > 0 || flow[v][u] > 0){
					vis[v] = 1;
					par[v] = u;
					if(v==T){
						augmented = true;
						int f = augment_path(T,INF);
						max_flow+=f;
						break;
					} else {
						q.push(v);
					}
				}
			}
			if(augmented)break;
		}
		if(!augmented)break;
	}
	return (max_flow == males);
}

long long dist[500][500],DINF = (long long) 1e14;
int bfs[30][30];
int Q, R;

void next_bfs(int x,int y,int d,queue<pair<pair<int,int>,int> > &q){
	if(x<0||y<0||x>=N||y>=M)return;
	if(cell[x][y] != '#' && !bfs[x][y]){
		bfs[x][y] = 1;
		q.push(make_pair(make_pair(x,y),d+1));
	}
}

void get_dist(int i,int r,int c,int t){
	--r;--c;
	for(int i=0;i<30;++i)for(int j=0;j<30;++j)bfs[i][j]=0;
	queue<pair<pair<int,int>,int> > q;
	q.push(make_pair(make_pair(r,c),0));
	bfs[r][c]=1;
	while(!q.empty()){
		int x = q.front().first.first;
		int y = q.front().first.second;
		int d = q.front().second;
		q.pop();
		dist[i][x*M+y+Q] = 1LL*d*t;
		next_bfs(x-1,y,d,q);
		next_bfs(x,y-1,d,q);
		next_bfs(x+1,y,d,q);
		next_bfs(x,y+1,d,q);
	}
}

bool solve(long long max_dist) {
	for(int i=0;i<500;++i){
		for(int j=0;j<500;++j){
			cap[i][j] = flow[i][j] = 0;
		}
	}
	adj = vector<vector<int> > (503);
	for(int i=Q;i<R;++i){
		adj[i].push_back(i+M*N);
		adj[i+M*N].push_back(i);
		cap[i][i+M*N] = 1;
	}
	for(int i=0;i<Q;++i){
		if(i<males){
			cap[S][i] = 1;
			adj[S].push_back(i);
			adj[i].push_back(S);
		}
		else {
			cap[i][T] = 1;
			adj[i].push_back(T);
			adj[T].push_back(i);
		}
		for(int j=Q;j<R;++j){
			if(dist[i][j]<=max_dist){
				if(i<males){
					cap[i][j]=1;
					adj[i].push_back(j);
					adj[j].push_back(i);
				} else {
					cap[j+M*N][i]=1;
					adj[j+M*N].push_back(i);
					adj[i].push_back(j+M*N);
				}
			}
		}
	}
	return edmondskarp();
}

int main(){
	possible = false;
	int r,c,t;
	scanf("%d%d%d%d",&N,&M,&males,&females);
	if(males+1!=females && females+1!=males){
		printf("-1\n"); return 0;
	}
	bool is_male = false;
	if(males < females){
		++males;
		is_male = true;
	} else {
		++females;
	}
	Q = males+females;
	R = Q + N*M;
	for(int i=0;i<N;++i){
		cin >> cell[i];
	}
	for(int i=0;i<500;++i){
		for(int j=0;j<500;++j){
			dist[i][j] = DINF;
		}
	}
	scanf("%d%d%d",&r,&c,&t);
	if(is_male){
		get_dist(0,r,c,t);
	} else {
		get_dist(males,r,c,t);
	}
	for(int i=(is_male?1:0);i<males;++i){
		scanf("%d%d%d",&r,&c,&t);
		get_dist(i,r,c,t);
	}
	for(int i=(is_male?males:males+1);i<males+females;++i){
		scanf("%d%d%d",&r,&c,&t);
		get_dist(i,r,c,t);
	}
	long long lo = 0, hi=(long long)1e13, mid;
	while(lo<=hi){
		mid = (lo+hi)/2LL;
		if(solve(mid)){
			possible = true;
			hi = mid-1LL;
		} else {
			lo = mid+1LL;
		}
	}
	if(possible)cout << lo << endl;
	else printf("-1\n");
}