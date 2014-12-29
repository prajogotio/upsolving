#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <map>
#include <string>
using namespace std;

//WRONG INTERPRETATION OF THE PROBLEM. REPLACEMENT RULES ARE NOT VICE VERSA


int N, M;
map<string,int> idx;
vector<vector<int> > adj;
string s, t;
vector<pair<int,int> > val;
vector<int> text;
int vis[200003];
int ff[200003];
int dp[200003][2];

void dfs(int u, int col){
	vis[u] = 1;
	ff[u] = col;
	if(dp[col][0] == val[u].first){
		if(dp[col][1] > val[u].second){
			dp[col][1] = val[u].second;
		}
	} else if (dp[col][0] > val[u].first){
		dp[col][0] = val[u].first;
		dp[col][1] = val[u].second;
	}
	for(int i=0;i<adj[u].size();++i){
		int v = adj[u][i];
		if(vis[v])continue;
		dfs(v, col);
	}
}

int main(){
	int n = 0;
	scanf("%d", &N);
	for(int i=0;i<N;++i){
		cin >> s;
		int cnt = 0;
		for(int i=0;i<s.size();++i){
			s[i] = tolower(s[i]);
			if(s[i] == 'r') ++cnt;
		}
		if(idx.find(s) == idx.end()){
			idx[s] = n++;
			val.push_back(make_pair(cnt, s.size()));
		}
		text.push_back(idx[s]);
	}
	scanf("%d", &M);
	adj = vector<vector<int> >(200003);
	for(int i=0;i<M;++i){
		cin >> s; cin >> t;
		int cnt = 0;
		for(int i=0;i<s.size();++i){
			s[i] = tolower(s[i]);
			if(s[i] == 'r') ++cnt;
		}
		if(idx.find(s) == idx.end()){
			idx[s] = n++;
			val.push_back(make_pair(cnt, s.size()));
		}
		cnt = 0;
		for(int i=0;i<t.size();++i){
			t[i] = tolower(t[i]);
			if(t[i] == 'r') ++cnt;
		}
		if(idx.find(t) == idx.end()){
			idx[t] = n++;
			val.push_back(make_pair(cnt, t.size()));
		}
		int u = idx[s];
		int v = idx[t];
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for(int i=0;i<=200000;++i)
		for(int j=0;j<2;++j)
			dp[i][j] = 1234567;
	int len = 0, ans = 0;
	int col = 1;
	for(int i=0;i<text.size();++i){
		int u = text[i];
		if(!vis[u]) dfs(u, col++);
		ans += dp[ff[u]][0];
		len += dp[ff[u]][1];
		printf("%d %d\n", ans, len);
	}
	printf("%d %d\n", ans, len);
	return 0;
}