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
int par[100005];
int f[100005];
int counted[100005];
int det[100005];
vector<pair<int,int> > pq;
vector<vector<pair<int,int> > > adj;
int col[100005];
int vis[100005];
map<pair<int,int>, int> check;
map<pair<int,int>, int> cell;
int odd, even;
bool inconsistent;

//WRONG APPROACH


//DSU
void init(int N) {
	for(int i=0;i<=N+3;++i) {
		par[i] = i;
		det[i] = -1;
		col[i] = -1;
	}
	inconsistent = false;
}

int get_par(int i) {
	return (par[i] == i ? i : (par[i] = get_par(par[i])));
}

void merge(int i, int j) {
	int x = get_par(i); 
	int y = get_par(j);
	if(x == y) return;
	if(x < y) {
		par[y] = x;
	} else {
		par[x] = y;
	}
}

int get_cell(int i, int j) {
	if(cell.find(make_pair(i,j)) != cell.end()) {
		return cell[make_pair(i,j)];
	} else {
		return -1;
	}
}


void dfs(int u, int r) {
	vis[u] = 1;
	if(inconsistent) return;
	if(col[u] != -1) {
		if(col[u] != r) {
			inconsistent = true;
			return;
		}
	} else {
		col[u] = r;
		for(int i=0;i<adj[u].size();++i) {
			int v = adj[u][i].first;
			int m = adj[u][i].second;
			if(vis[v]) continue;
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
		cell[make_pair(u,v)] = (ch == 'o' ? 1 : 0);
		if(ch == 'o') val.push_back(1);
		else val.push_back(0);
	}
	adj = vector<vector<pair<int,int> > >(N+3);
	int a[4];
	for(int i=0;i<E;++i){
		u = eqn[i].first;
		v = eqn[i].second;
		a[0] = get_cell(u-1, v);
		a[1] = get_cell(u, v+1);
		a[2] = get_cell(u+1, v);
		a[3] = get_cell(u, v-1);
		int ctr = 0;
		for(int j=0;j<4;++j){
			if(a[j] == -1) continue;
			ctr += a[j];
		}
		if(ctr%2 != 0) {
			printf("0\n");
			return;
		}
	}
	if(N%2 == 0) {
		even = N+1;
		odd = N;
	} else {
		even = N;
		odd = N+1;
	}
	int L, R;
	init(N);
	for(int i = 0; i < E; ++i) {
		u = eqn[i].first;
		v = eqn[i].second;
		k = val[i];
		L = (u-v > 0 ? u-v : v-u);
		R = (0 > u+v - N ? u+v : 2*(N-1) - (u+v));
		adj[L].push_back(make_pair(R+1,k));
		if(check.find(make_pair(L,R+1)) != check.end() && check[make_pair(L,R+1)] != k) {
			printf("0\n");
			return;
		}
		if(det[L] != -1 && det[R+1] != -1) {
			if((det[L] ^ det[R+1]) != k) {
				printf("0\n");
				return;
			}
		}
		int x = f[get_par(L)] | f[get_par(R+1)];
		f[get_par(L)] = f[get_par(R+1)] = x;
		merge(L, R+1);
		check[make_pair(L,R+1)] = k;
		if(R+1 == (((u+v)%2==0) ? even : odd)) {
			if(det[L] != -1 && k != det[L]) {
				printf("0\n");
				return;
			}
			det[L] = k;
			f[get_par(L)] = 1;
		}
	}
	long long ans = 1;
	int diff = 0;
	for(int i=0;i<N;++i) {
		//printf("%d: %d %d\n", i, get_par(i), f[i]);
		if(counted[get_par(i)]) continue;
		counted[get_par(i)] = 1;
		inconsistent = false;
		/*
		for(int j=0;j<N;++j) {
			col[j] = -1;
			vis[j] = 0;
		}
		*/
		memset(col, -1, sizeof(col));
		memset(vis, 0, sizeof(vis));
		dfs(get_par(i), 0);
		if(inconsistent) {
			printf("0\n");
			return;
		}
		if(!f[get_par(i)]) ++diff;
	}
	//printf("\n");
	for(int i=0;i<diff;++i) {
		ans = (ans * 2) % (1000000007);
	}
	cout << ans << endl;
}

int main() {
	solve();
	return 0;
}