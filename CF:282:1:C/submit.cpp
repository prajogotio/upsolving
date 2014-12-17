#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

long long segtree[400005];
long long a[100005];
vector<pair<pair<int,int>, double> > r;
double prob[5003][5003];
vector<vector<int> > adj;
int vis[5003][5003];
long long rma[5003];
int N, Q;

void build_segtree(int p, int L, int R){
	if(L==R){
		segtree[p] = a[L];
		return;
	}
	int M = (L+R)/2;
	build_segtree(2*p, L, M);
	build_segtree(2*p+1, M+1, R);
	segtree[p] = max(segtree[2*p], segtree[2*p+1]);
}

long long rmq(int p, int L, int R, int S, int T) {
	if(R < S || T < L) return -1;
	if(S <= L && R <= T) {
		return segtree[p];
	}
	int M = (L+R)/2;
	long long left = rmq(2*p, L, M, S, T);
	long long right = rmq(2*p + 1, M+1, R, S, T);
	if(left < 0) return right;
	if(right < 0) return left;
	return max(right, left);
}

long long query(int u){
	if(rma[u] != -1) return rma[u];
	int L = r[u].first.first;
	int R = r[u].first.second;
	return (rma[u] = rmq(1, 0, N-1, L, R));
}

int fn(const pair<pair<int,int>, double> &L,
	   const pair<pair<int,int>, double> &R) {
	if(L.first.first == R.first.first) {
		return (L.first.second > R.first.second);
	}
	return L.first.first < R.first.first;
}

double pd(int u, int k){
	if(k > 5000) return 1;
	if(vis[u][k]) return prob[u][k];
	prob[u][k] = 1;
	if(adj[u].empty()){
		if(k == 0) prob[u][k] = (1-r[u].second);
	} else {
		double choose = 1;
		double no_choose = 1;
		for(int i=0;i<adj[u].size();++i){
			int v = adj[u][i];
			int diff = (int) (query(u) - query(v));
			//choose
			if(k > 0){
				choose *= pd(v, diff+k-1); 
			}
			//don't choose
			no_choose *= pd(v, diff+k);
		}
		prob[u][k] = (1.0 - r[u].second) * no_choose;
		if(k > 0) prob[u][k] += r[u].second * choose;
	}
	vis[u][k] = 1;
	return prob[u][k];
}

int main(){
	int u,v;
	double p;
	scanf("%d%d", &N, &Q);
	for(int i=0;i<N;++i){
		scanf("%lldd", &a[i]);
	}
	r.push_back(make_pair(make_pair(0,N-1),0));
	for(int i=0;i<Q;++i){
		scanf("%d%d %lf", &u, &v, &p);
		r.push_back(make_pair(make_pair(u-1,v-1), p));
	}
	sort(r.begin(), r.end(), fn);
	adj = vector<vector<int> > (Q+3);
	for(int i=0;i<Q+1;++i){
		for(int j=i+1;j<=Q;++j){
			if(r[i].first.first <= r[j].first.first
			&& r[i].first.second >= r[j].first.second) {
				if(!adj[i].empty() && r[adj[i].back()].first.first <= r[j].first.first &&
				   r[adj[i].back()].first.second >= r[j].first.second) 
					continue;
				adj[i].push_back(j);
			} else {
				break;
			}
		}
	}
	for(int i=0;i<=Q;++i)rma[i] = -1;
	build_segtree(1, 0, N-1);
	double ans = 0;
	long long mf = query(0);
	double prev = 0;
	for(int i=0;i<=Q;++i){
		double tmp = pd(0, i);
		ans += (tmp - prev) * (mf+i);
		prev = tmp;
	}
	printf("%.12lf\n", ans);
	return 0;
}