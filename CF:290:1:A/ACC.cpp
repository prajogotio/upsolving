#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <queue>
#include <cmath>
#include <cassert>
#include <map>
#include <set>
using namespace std;

int s[103][103];
int g[103][103];
int indeg[30], vis[30];
int N;
vector<vector<int> > adj;
vector<int> S, T;
int $ = 26;

int main(){
	string t;
	scanf("%d",&N);
	int maxlen = 0;
	for(int i=0;i<N;++i){
		cin >> t;
		for(int j=0;j<100;++j){
			if(j<t.size()){
				s[i][j] = t[j]-'a';
			} else {
				s[i][j] = $;
			}
		}
		maxlen = max(maxlen, (int) t.size());
	}
	adj = vector<vector<int> > (30);
	for(int i=0;i<26;++i){
		adj[26].push_back(i);
		indeg[i]++;
	}
	for(int j=0;j<maxlen;++j){
		int k = 0;
		int prev = $;
		for(int i=0;i<N;++i){
			if(prev != s[i][j]) {
				++k;
				prev = s[i][j];
			} else if(j != 0 && i != 0 && g[i-1][j-1] != g[i][j-1]) {
				++k;
			}
			g[i][j] = k;
		}
		for(int i=1;i<N;++i){
			if(g[i][j] != g[i-1][j]) {
				if(j==0 || g[i][j-1] == g[i-1][j-1]) {
					adj[s[i-1][j]].push_back(s[i][j]);
					//printf("%c => %c\n",s[i-1][j]+'a',s[i][j]+'a');
					indeg[s[i][j]]++;
				}
			}
		}
	}
	bool not_empty = false;
	for(int i=0;i<=$;++i){
		if(adj[i].empty()) continue;
		not_empty = true;
		if(indeg[i] == 0) S.push_back(i);
	}
	if(S.empty() && not_empty) {
		printf("Impossible\n");
		return 0;
	}
	while(!S.empty()){
		int u = S.back();
		vis[u] = 1;
		S.pop_back();
		T.push_back(u);
		for(int i=0;i<adj[u].size();++i){
			int v = adj[u][i];
			//printf("%c->%c\n",u+'a',v+'a');
			indeg[v]--;
			if(indeg[v]==0) S.push_back(v);
		}
	}
	for(int i=0;i<=$;++i){
		if(indeg[i]!=0){
			//printf("%c\n",i+'a');
			printf("Impossible\n");
			return 0;
		}
		if(vis[i]==0) T.push_back(i);
	}
	for(int i=0;i<T.size();++i){
		if(T[i]==$)continue;
		printf("%c", T[i]+'a');
	}
	printf("\n");
	return 0;
}