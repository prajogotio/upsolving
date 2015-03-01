#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

vector<vector<int> > adj;
vector<vector<int> > chains;
int sz[100005], vis[100005];
int sc[100005], cmp[100005], pos[100005], par_chain[100005], par[100005];
int N;
vector<int> euler;
vector<int> segtree;
int depth[100005];
int a[100005];

int lca;
int mark[100005];
int iter;
bool parent_used;
int right_below[2];
int state;

int mabs(int x) {return (x > 0 ? x : -x);}

int dfs(int u, int d) {
	vis[u] = 1;
	euler.push_back(u);
	a[u] = euler.size()-1;
	depth[u] = d;
	int child = 0;
	int schild[2] = {-1, 0};
	for(int i=0;i<adj[u].size();++i){
		int v=adj[u][i];
		if(vis[v])continue;
		par[v] = u;
		child += dfs(v, d+1);
		euler.push_back(u);
		if(schild[1]<sz[v]) {
			schild[0] = v;
			schild[1] = sz[v];
		}
	}
	sz[u] = child+1;
	sc[u] = schild[0];
	return sz[u];
}

void HLD(int cur, int chain) {
	cmp[cur] = chain;
	chains[chain].push_back(cur);
	pos[cur] = chains[chain].size()-1;
	if(sc[cur] == -1) return;
	HLD(sc[cur], chain);
	for(int i=0;i<adj[cur].size();++i){
		int v = adj[cur][i];
		if(sc[cur] == v) continue;
		if(cmp[v] != -1) continue;
		chains.push_back(vector<int>());
		cmp[v] = chain;
		par_chain[cmp[v]] = cmp[cur];
		HLD(v, (int) chains.size()-1);
	}
}

void build(int p, int L, int R) {
	if(L==R) {
		segtree[p] = euler[L];
		return;
	}
	int M = (L+R)/2;
	build(2*p, L, M);
	build(2*p+1, M+1, R);
	segtree[p] = (depth[segtree[2*p]] < depth[segtree[2*p+1]] ? segtree[2*p] : segtree[2*p+1]);
}

int rmq(int p, int L, int R, int S, int T) {
	if(R < S || T < L) return -1;
	if(S <= L && R <= T) {
		return segtree[p];
	}
	int M = (L+R)/2;
	int left = rmq(2*p, L, M, S, T);
	int right = rmq(2*p+1, M+1, R, S, T);
	if(left == -1) return right;
	if(right == -1) return left;
	return (depth[left] < depth[right] ? left : right);
}


int dist_up(int u, int lca) {
	if(cmp[u] == cmp[lca]) return mabs(pos[lca] - pos[u]);
	int head = chains[cmp[u]][0];
	return pos[u] + 1 + dist_up(par[head], lca);
}

int LCA(int u, int v) {
	int left = min(a[u], a[v]);
	int right = max(a[u], a[v]);
	return rmq(1, 0, euler.size()-1, left, right);
}

int dist(int u, int v) {
	//int lca = LCA(u, v);
	// printf("%d -> %d\n%d -> %d\n",u, a[u], v, a[v]);
	// printf("%d <- %d -> %d\n", u, lca, v);
	//return dist_up(u, lca) + dist_up(v,lca);
	return mabs(depth[lca] - depth[u]) + mabs(depth[lca] - depth[v]);
}

int search_up(int u, int v, int d) {
	if(d <= pos[u]) {
		if(d!=0){
			// printf("[%d] ",chains[cmp[u]][pos[u]-d+1]);
			mark[chains[cmp[u]][pos[u]-d+1]] = iter;
			right_below[state] = chains[cmp[u]][pos[u]-d+1];
		}
		return chains[cmp[u]][pos[u]-d];
	}
	int head = chains[cmp[u]][0];
	mark[head] = iter;
	right_below[state] = head;
	// printf("%d ", head);
	return search_up(par[head], v, d-pos[u]-1);
}

int find(int u, int v, int d) {
	//int lca = LCA(u,v);
	//int u_lca = dist_up(u, lca);
	int u_lca = dist(u, lca);
	//int v_lca = dist_up(v, lca);
	// printf("%d->%d = %d\n",u, lca, u_lca);
	// printf("%d->%d = %d\n",v, lca, v_lca);
	if(/*u_lca == v_lca && */u_lca == d) {
		state = 0;
		search_up(u, lca, d);
		state = 1;
		search_up(v, lca, d);
		return lca;
	} else if(u_lca < d) {
		//printf("up from %d by %d\n",v, v_lca + u_lca - d);
		//int v_lca = dist_up(v, lca);
		int v_lca = dist(v, lca);
		parent_used = true;
		state = 0;
		return search_up(v, lca, v_lca + u_lca - d);
	} else {
		parent_used = true;
		state = 0;
		return search_up(u, lca, d);
	}
}

int number_of_child(int pivot) {
	int ans = 0;
	// printf("added: ");
	// for(int i=0;i<adj[pivot].size(); ++i) {
	// 	int v = adj[pivot][i];
	// 	if(mark[v] != iter && par[pivot] != v){
	// 		//printf("%d ",v);
	// 		ans += sz[v];
	// 	}
	// }
	// printf("#\n");
	// printf("parent:%d\n",par[pivot]);
	// printf("total currently = %d\n",ans);
	if(parent_used && pivot != 1) {
		return sz[pivot] - sz[right_below[0]];
	}
	return N - (sz[right_below[0]] + sz[right_below[1]]);
}

int main(){
	int u, v;
	scanf("%d",&N);
	adj = vector<vector<int> > (N+3);
	for(int i=0;i<N-1;++i){
		scanf("%d%d",&u,&v);
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	for(int i=0;i<=N;++i){
		cmp[i] = -1;
		sc[i] = -1;
	}
	dfs(1, 0);
	segtree = vector<int>(4*(int)euler.size());
	build(1, 0, euler.size()-1);
	chains.push_back(vector<int>());
	HLD(1, 0);
	int Q;
	scanf("%d",&Q);
	sz[0] = 0;
	for(int qq=0;qq<Q;++qq){
		//printf("+++++++++++++++++++\n");
		right_below[0] = right_below[1] = 0;
		parent_used = false;
		++iter;
		int x, y;
		scanf("%d%d",&x,&y);
		lca = LCA(x,y);
		int d = dist(x,y);
		if(d%2) {
			printf("0\n");
			continue;
		}
		//printf("equidist[%d,%d] = %d\n", x, y, d/2);
		int pivot = find(x, y, d/2);
		//printf("\n");
		//printf("pivot = %d\n",pivot);
		printf("%d\n",number_of_child(pivot));
	}
	return 0;
}