#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
using namespace std;

int adj[100005][27];
int win[100005];	//can first person win if start at node u?
int lose[100005];   //can first person lose if start at node u?
int N, K, node;
string s[100005];

void build(int n){
	int cur = 1;
	int k = 0;
	int sz = s[n].size();
	while(k<sz && adj[cur][s[n][k]-'a']){
		cur = adj[cur][s[n][k]-'a'];
		++k;
	}
	while(k<sz){
		adj[cur][s[n][k]-'a'] = ++node;
		cur = node;
		++k;
	}

}

void build_win_lose(int u){
	bool isleaf = true;
	win[u] = lose[u] = 0;
	for(int i=0;i<26;++i){
		if(!adj[u][i])continue;
		isleaf=false;
		build_win_lose(adj[u][i]);
		if(win[adj[u][i]]==0)win[u]=1;
		if(lose[adj[u][i]]==0)lose[u]=1;
	}
	if(isleaf){
		win[u] = 0;
		lose[u] = 1;
	}
}

int main(){
	scanf("%d%d",&N,&K);
	for(int i=0;i<N;++i){
		cin >> s[i];
	}
	node = 1;
	for(int i=0;i<N;++i){
		build(i);
	}
	build_win_lose(1);
	//printf("%d %d\n", win[1], lose[1]);
	if(win[1]&&lose[1]){
		printf("First\n");
	} else {
		if(win[1]){
			if(K%2)printf("First\n"); else printf("Second\n");
		} else {
			printf("Second\n");
		}
	}
	return 0;
}