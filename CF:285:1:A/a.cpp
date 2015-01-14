#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

priority_queue<pair<int,int> > st;
vector<pair<int,int> > ans;
int degree[70000], s[70000];
vector<vector<int> > adj;
int N;
int main(){
	int u,v,w;
	scanf("%d",&N);
	for(int i=0;i<N;++i){
		scanf("%d %d",&u,&v);
		st.push(make_pair(-u,i));
		degree[i] = u;
		s[i] = v;
	}
	adj = vector<vector<int> >(N+3);
	while(!st.empty()){
		u = st.top().second;
		v = -st.top().first;
		w = s[u];
		st.pop();
		if(degree[u] == adj[u].size())continue;
		for(int i=0;i<adj[u].size();++i){
			w ^= adj[u][i];
		}
		adj[u].push_back(w);
		adj[w].push_back(u);
		st.push(make_pair(adj[w].size()-degree[w], w));
		ans.push_back(make_pair(u,w));
	}
	printf("%d\n",(int)ans.size());
	for(int i=0;i<ans.size();++i){
		printf("%d %d\n", ans[i].first, ans[i].second);
	}
	return 0;
}