#include <iostream>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstring>
using namespace std;
long long INF = (long long) 1e10;
int vis[2003];
int dist[2003][2003];
int idx[2003];
int height[2003];
int segtree[16003];
int head[2003];
long long d[2003];
vector<int> euler;
vector<vector<int> > tree;
int n;
bool ok = true;

void djikstra(int source){
	for(int i=0;i<n;++i){
		d[i] = INF;
	}
	d[source] = 0;
	head[source] = source;
	int cnt = 0;
	while(cnt != n){
		int cur = -1;
		for(int i=0;i<n;++i){
			if(vis[i]) continue;
			if(cur == -1 || d[cur] > d[i]){
				cur = i;
			}
		}
		if(d[cur] == 0 && cur != source) {
			ok = false;
			break;
		}
		vis[cur] = 1;
		if(head[cur] != cur) {
			tree[head[cur]].push_back(cur);
			tree[cur].push_back(head[cur]);
		}
		for(int i=0;i<n;++i){
			if(vis[i]) continue;
			if(d[i] >= d[cur] + dist[cur][i]){
				d[i] = d[cur] + dist[cur][i];
				head[i] = cur;
			}
		}
		++cnt;
	}
}

void dfs(int u, int level) {
	vis[u] = 1;
	euler.push_back(u);
	idx[u] = euler.size()-1;
	height[u] = level;
	for(int i=0;i<tree[u].size();++i){
		int v = tree[u][i];
		if(vis[v]) continue;
		dfs(v, level+1);
		euler.push_back(u);
	}
}

void build(int p, int L, int R){
	if(L==R){
		segtree[p] = euler[L];
		return;
	}
	int M = (L+R)/2;
	build(2*p, L, M);
	build(2*p+1, M+1, R);
	segtree[p] = (height[segtree[2*p]] < height[segtree[2*p+1]] ? segtree[2*p] : segtree[2*p+1]);
}

int rmq(int p, int L, int R, int S, int T){
	if(R < S || T < L) return -1;
	if(S <= L && R <= T) {
		return segtree[p];
	}
	int M = (L+R)/2;
	int left = rmq(2*p, L, M, S, T);
	int right = rmq(2*p+1, M+1, R, S, T);
	if(left == -1) return right;
	if(right == -1) return left;
	return (height[left] < height[right] ? left : right);
}


int main(){
	scanf("%d", &n);
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			scanf("%d", &dist[i][j]);
		}
	}
	tree = vector<vector<int> > (n+3);
	d[0] = 0;
	djikstra(0);
	if(!ok){
		printf("NO\n");
		return 0;
	}
	memset(vis, 0, sizeof vis);
	dfs(0,0);
	build(1,0,euler.size()-1);
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			if(idx[j] < idx[i]) continue;
			int par = rmq(1, 0, euler.size()-1, idx[i], idx[j]);
			if(i == par || par == j || i == j) {
				int tmp = max(d[i]-d[j], d[j] - d[i]);
				if(dist[i][j] != tmp || dist[i][j] != dist[j][i]){
					ok = false;
					break;
				}
			} else {
				if(dist[i][j] != d[i] + d[j] - 2*d[par] ||
				   dist[j][i] != dist[j][i]) {
					ok = false;
					break;
				}
			}
		}
		if(!ok)break;
	}
	if(ok) printf("YES\n");
	else printf("NO\n");
	return 0;
}