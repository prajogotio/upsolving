#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
using namespace std;

int vis[100005];

vector<vector<pair<int,int> > > adj;
vector<pair<int,int> > color[100005];
set<int> group[100005];
map<pair<int,int>,int> ans;
int N,M,Q;
vector<int> S;
int curtime;
void dfs(int u,int c){
	vis[u] = curtime;
	S.push_back(u);
	for(int i=0;i<adj[u].size();++i){
		int v = adj[u][i].first;
		int col = adj[u][i].second;
		if(col != c)continue;
		if(vis[v]==curtime)continue;
		dfs(v,c);
	}
}

int main(){
	scanf("%d%d",&N,&M);
	int u,v,c;
	adj = vector<vector<pair<int,int> > > (N+3);
	for(int i=0;i<M;++i){
		scanf("%d%d%d",&u,&v,&c);
		color[c].push_back(make_pair(u,v));
		adj[v].push_back(make_pair(u,c));
		adj[u].push_back(make_pair(v,c));
	}
	curtime = 0;
	int ctr = 0;
	for(int i=1;i<=M;++i){
		if(color[i].empty())continue;
		++curtime;
		set<int> st;
		for(int j=0;j<color[i].size();++j){
			st.insert(color[i][j].first);
			st.insert(color[i][j].second);
		}
		for(set<int>::iterator j=st.begin();j!=st.end();++j){
			u = *j;
			if(vis[u]==curtime)continue;
			dfs(u,i);
			while(!S.empty()){
				v = S.back();
				S.pop_back();
				group[v].insert(ctr);
			}
			++ctr;
		}
		printf("%d\n",i);
	}
	scanf("%d",&Q);
	for(int qq=0;qq<Q;++qq){
		scanf("%d%d",&u,&v);
		if(v<u)swap(u,v);
		if(ans.find(make_pair(u,v))==ans.end()){
			int ret = 0;
			set<int>::iterator uit = group[u].begin(),vit = group[v].begin();
			while(uit != group[u].end() && vit != group[v].end()){
				if(*uit == *vit) {
					++ret;
					uit++;
					vit++;
				} else {
					if(*uit < *vit) ++uit;
					else ++vit;
				}
			}
			ans[make_pair(u,v)] = ret;
			printf("%d\n",ret);
		} else {
			printf("%d\n",ans[make_pair(u,v)]);
		}
	}
	return 0;
}