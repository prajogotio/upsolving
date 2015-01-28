#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

// Represent the strings as nodes, and i have to solve for hamiltonian path
// Represent the strings as edges, and i only need to solve for euler path!

vector<vector<pair<int,int> > > adj;
int indeg[62*62];
int vis[200005];
string edge[200005];
//vector<vector<int> > S, T;
vector<int> S, T;
int N;
int mark[62*62];
int source = 0, sink = 0;

int f(string s) {
	int ret = 0;
	for(int i=0;i<3;++i){
		ret *= 62;
		if(s[i] < 'A') {
			ret += s[i] -'0';
		} else if(s[i]<'a') {
			ret += s[i]-'A'+10;
		} else {
			ret += s[i]-'a'+36;
		}
	}
	return ret;
}
/*
void dfs(int u) {
	bool traverse = false;
	for(int i=0;i<adj[u].size();++i){
		int e = adj[u][i].second;
		int v = adj[u][i].first;
		if(vis[e]) continue;
		traverse = true;
		vis[e] = 1;
		S.back().push_back(e);
		dfs(v);
	}
	if(traverse == false) {
		S.push_back(vector<int>());
	}
}
*/
void dfs(int u) {
	while(!adj[u].empty()){
		int v = adj[u].back().first;
		int e = adj[u].back().second;
		//if(vis[e])continue;
		adj[u].pop_back();
		T.push_back(e);
		vis[e] = 1;
		dfs(v);
		while(!T.empty()){
			S.push_back(T.back());
			T.pop_back();
			if(S.back() == e) break;
		}
	}
}
int main() {
	scanf("%d",&N);
	adj = vector<vector<pair<int,int> > >(62*62+3);
	for(int i=0;i<N;++i){
		cin >> edge[i];
		int p = f(edge[i]);
		int a = p/62;
		int b = p%(62*62);
		//printf("%d %d %d\n", p,a,b);
		adj[a].push_back(make_pair(b, i));
		indeg[b]++;
	}
	source = -1; sink = -1;
	bool foundsource = false;
	bool foundsink = false;
	for(int i=0;i<62*62;++i){
		int outdeg = adj[i].size();
		if(outdeg > 0 && !foundsource){
			//if(source == -1 || outdeg > adj[source].size())
				source = i;
		}
		if(outdeg - indeg[i] == 1) {
			if(foundsource) {
				printf("NO\n"); return 0;
			}
			source = i;
			foundsource = true;
		}
		else if(indeg[i] - outdeg == 1) {
			if(foundsink) {
				printf("NO\n"); return 0;
			}
			sink = i;
			foundsink = true;
		}
		else if(indeg[i] - outdeg != 0) {
			printf("NO\n"); return 0;
		}
	}
	if(foundsource != foundsink) {
		printf("NO\n"); return 0;
	}
	
	//S.push_back(vector<int>());
	dfs(source);
	for(int i=0;i<N;++i){
		if(!vis[i]) {
			printf("NO\n"); return 0;
		}
	}
	printf("YES\n");
	/*
	bool flag = false;
	for(int i=S.size()-1;i>=0;--i){
		for(int j=0;j<S[i].size();++j){
			if(!flag){
				printf("%s",edge[S[i][j]].c_str());
				flag = true;
			}
			else printf("%c",edge[S[i][j]][2]);
		}
	}
	printf("\n");
	*/
	bool flag = false;
	while(!S.empty()){
		if(!flag){
			printf("%s", edge[S.back()].c_str());
			flag = true;
		} else {
			printf("%c", edge[S.back()][2]);
		}
		S.pop_back();
	}
	printf("\n");
	return 0;
}