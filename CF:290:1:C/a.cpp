#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

/*
Every odd number must have 2 even number as its neighbor, and vice versa
source -> 2 -> odd -> even -> 2 -> sink
*/
int mark[100000];
int cap[203][203], f[203][203];
int val[203], par[203];
int N, S=201, T=202;
int maxflow = 0;
int odd = 0, even = 0;
int vis[203];
int INF = 1234567;
vector<vector<int> > adj;
vector<vector<int> > temp;
int augment_path(int v, int mf){
	int u = par[v];
	if(v == S) {
		return mf;
	}
	bool backedge = false;
	if(cap[u][v]-f[u][v] <= 0 && f[v][u] > 0) backedge = true;
	if(backedge) {
		mf = min(mf, f[v][u]);
	} else {
		mf = min(mf, cap[u][v] - f[u][v]);
	}
	mf = augment_path(u, mf);
	if(backedge) {
		f[v][u] -= mf;
	} else {
		f[u][v] += mf;
	}
	return mf;
}

void edmondskarp() {
	maxflow = 0;
	while(1) {
		bool augmented = false;
		for(int i=0;i<203;++i)vis[i] = 0;
		queue<int> q;
		q.push(S);
		vis[S] = 1;
		while(!q.empty()){
			int u = q.front();
			q.pop();
			for(int i=0;i<203;++i){
				if((cap[u][i]-f[u][i]>0 || f[i][u] > 0)  && !vis[i]) {
					vis[i] = 1;
					par[i]=u;
					if(i==T) {
						maxflow += augment_path(T, INF);
						augmented = true;
						break;
					}
					else q.push(i);
				}
			}
			if(augmented)break;
		}
		if(!augmented)break;
	}
}

void dfs(int u) {
	vis[u] = 1;
	temp.back().push_back(u);
	for(int i=0;i<adj[u].size();++i){
		if(vis[adj[u][i]])continue;
		dfs(adj[u][i]);
	}
}

int main(){
	for(int i=2;i*i<100000;++i){
		for(int j=i;j*i<100000;++j){
			mark[i*j] = 1;
		}
	}
	scanf("%d",&N);
	for(int i=0;i<N;++i){
		scanf("%d",&val[i]);
		//printf("%d: %d\n",i,val[i]);
	}
	for(int i=0;i<N;++i){
		if(val[i]%2) {
			cap[S][i] = 2;
			++odd;
		} else {
			cap[i][T] = 2;
			++even;
		}
		for(int j=i+1;j<N;++j){
			if(mark[val[i]+val[j]])continue;
			if(val[i]%2)cap[i][j] = 1;
			else cap[j][i] = 1;
		}
	}
	// for(int i=0;i<N;++i){
	// 	for(int j=0;j<N;++j){
	// 		printf("%d ",cap[i][j]);
	// 	}
	// 	printf("\n");
	// }
	edmondskarp();
	// for(int i=0;i<N;++i){
	// 	for(int j=0;j<N;++j){
	// 		printf("(%d,%d) ",cap[i][j], f[i][j]);
	// 	}
	// 	printf("\n");
	// }
	//printf("%d,%d,%d\n",even,odd,maxflow);
	if(odd * 2 != even * 2 || even * 2 != maxflow) {
		printf("Impossible\n");
		return 0;
	}
	adj = vector<vector<int> > (N+3);
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			if(cap[i][j] > 0 && f[i][j]>0){
				adj[i].push_back(j);
				adj[j].push_back(i);
			}
		}
	}
	for(int i=0;i<N;++i)vis[i]=0;
	for(int i=0;i<N;++i){
		if(vis[i])continue;
		temp.push_back(vector<int>());
		dfs(i);
	}
	printf("%d\n",(int)temp.size());
	for(int i=0;i<temp.size();++i){
		printf("%d", (int)temp[i].size());
		for(int j=0;j<temp[i].size();++j){
			printf(" %d",temp[i][j]+1);
		}
		printf("\n");
	}
	return 0;
}