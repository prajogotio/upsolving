#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;
int N,M;
vector<vector<int> > adj;
int par[100005];
int vis[100005];
int ctr;
int root_count;
int root;
vector<int> st;
vector<int> tmp;
void dfs(int u){
	vis[u] = 1;
	++ctr;
	bool isleaf = true;
	int parity = 1;
	st.push_back(u);
	for(int i=0;i<adj[u].size();++i){
		int v = adj[u][i];
		if(vis[v])continue;
		isleaf = false;
		dfs(v);
		st.push_back(u);
		++parity;
		if(!tmp.empty()){
			st.push_back(tmp.back());
			tmp.pop_back();
			st.push_back(u);
			++parity;
		}
	}
	if(u==root)root_count = parity;
	if(par[u]!=(parity%2))tmp.push_back(u);
}


int main(){
	int u,v;
	scanf("%d%d",&N,&M);
	adj = vector<vector<int> > (N+3);
	for(int i=0;i<M;++i){
		scanf("%d%d",&u,&v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for(int i=1;i<=N;++i){
		scanf("%d",&par[i]);
	}
	for(int i=1;i<=N;++i){
		if(par[i]==1){
			root = i;
			dfs(i);
			break;
		}
	}
	bool ok = true;
	for(int i=1;i<=N;++i){
		if(!vis[i]&&par[i])ok=false;
		if(!ok)break;
	}	
	if(ok){
		if((root_count%2)!=par[root]){
			if(!st.empty())st.pop_back();
			else st.push_back(root);
		}
		printf("%d\n",(int)st.size());
		for(int i=0;i<st.size();++i){
			if(i!=0)printf(" ");
			printf("%d",st[i]);
		}
		if(st.size()!=0)printf("\n");
	} else {
		printf("-1\n");
	}
	return 0;
}