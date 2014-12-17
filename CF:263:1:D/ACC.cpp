#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <cstring>
using namespace std;

int N, E;
vector<pair<int,int> > eqn;
vector<int> val;
vector<vector<pair<int,int> > > adj;
int col[100005];
int f[100005];
vector<pair<int,int> > p;
bool inconsistent;

void dfs(int u, int r) {
	if(inconsistent) return;
	if(col[u] != -1) {
		if(col[u] != r) {
			inconsistent = true;
		}
		return;
	} else {
		col[u] = r;
		for(int i=0;i<adj[u].size();++i) {
			int v = adj[u][i].first;
			int m = adj[u][i].second;
			dfs(v, r^m);
			if(inconsistent) return;
		}
	}
}

void solve() {
	scanf("%d %d", &N, &E);
	int u,v,k;
	char ch;
	for(int i=0;i<E;++i){
		scanf("%d %d %c", &u, &v, &ch);
		eqn.push_back(make_pair(u-1,v-1));
		if(ch == 'o') val.push_back(1);
		else val.push_back(0);
	}
	adj = vector<vector<pair<int,int> > >(N+3);
	int L, R;
	int even, odd;
	if(N%2 == 0) {
		even = N;
		odd = N+1;
	} else {
		odd = N+1;
		even = N;
	}
	for(int i = 0; i < E; ++i) {
		u = eqn[i].first;
		v = eqn[i].second;
		k = val[i];
		L = (u-v > 0 ? u-v : v-u);
		R = (0 > u+v - N ? u+v : 2*(N-1) - (u+v));
		if(R+2 == ((u+v)%2 == 0 ? even:odd)) {
			adj[L].push_back(make_pair(R+2,k));
			continue;
		}
		adj[L].push_back(make_pair(R+2,k));
		adj[R+2].push_back(make_pair(L,k));
	}
	long long ans = 1;
	int diff = 0;
	memset(col, -1, sizeof(col));
	inconsistent = false;
	for(int i=0;i<N;++i) {
		if(inconsistent) break;
		if(col[i] == -1) {
			col[even] = col[odd] = -1;
			dfs(i,0);
			if(col[even] == -1 && col[odd] == -1) ++diff;
		}
	}
	if(inconsistent) {
		printf("0\n");
		return;
	}
	for(int i=0;i<diff;++i) {
		ans = (ans * 2) % (1000000007);
	}
	cout << ans << endl;
}

int main() {
	solve();
	return 0;
}