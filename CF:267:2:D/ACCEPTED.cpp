#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <map>
#include <string>
using namespace std;



int N, M;
map<string,int> idx;
vector<vector<int> > adj;
string s, t;
vector<pair<long long,long long> > val;
vector<int> text;
int vis[200003];
long long dp[200003][2];
int col[200003];
int low[200003];
int mark, counter;
vector<int> S;

void tarjanscc(int u){
	S.push_back(u);
	vis[u] = counter;
	low[u] = counter++;
	for(int i=0;i<adj[u].size();++i){
		int v = adj[u][i];
		if(vis[v]){
			if(col[v] == 0){
				// in the current stack S, a backedge! get its index
				low[u] = min(low[u], vis[v]);
			} // otherwise, already belongs to another scc
		} else {
			// not yet visited
			tarjanscc(v);
			// update lowlink.
			low[u] = min(low[u], low[v]);
		}
		// in either case:
		// update val[u] whichever is lower
		if(dp[col[v]][0] == val[u].first){
			val[u].second = min(val[u].second, dp[col[v]][1]);
		} else if(dp[col[v]][0] < val[u].first){
			val[u].first = dp[col[v]][0];
			val[u].second = dp[col[v]][1];
		}
	}
	if(vis[u] == low[u]){
		// root of current SCC.
		//	update dp!
		while(!S.empty()){
			int v = S.back();
			S.pop_back();
			col[v] = mark;
			if(dp[mark][0] == val[v].first){
				dp[mark][1] = min(dp[mark][1], val[v].second);
			} else if(dp[mark][0] > val[v].first){
				dp[mark][0] = val[v].first;
				dp[mark][1] = val[v].second;
			}
			if(v == u) break;
		}
		++mark;
	} // else just return
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
	}
	for(int i=0;i<=200000;++i)
		for(int j=0;j<2;++j)
			dp[i][j] = 123456789LL;
	long long len = 0, ans = 0;
	mark = 1;
	counter = 1;
	for(int i=0;i<text.size();++i){
		int u = text[i];
		if(!vis[u]){
			tarjanscc(u);
		}
		ans += dp[col[u]][0];
		len += dp[col[u]][1];
	}
	cout << ans << " " << len << endl;
	return 0;
}