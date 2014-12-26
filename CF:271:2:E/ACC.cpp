#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
#include <cstring>
#include <cassert>
using namespace std;

int segtree[400005];
int par[100005];
vector<long long> val;
int tot[100005];
int idx[100005];
vector<pair<long long,int> > st;
int n, d;
int N;

int lowerbound(long long u){
	int lo = 0, hi = N-1, mid;
	while(lo <= hi){
		mid = (lo+hi)/2;
		if(val[mid] < u){
			lo = mid+1;
		} else {
			hi = mid-1;
		}
	}
	return lo;
}

int upperbound(long long u){
	int lo=0, hi=N-1, mid;
	while(lo<=hi){
		mid = (lo+hi)/2;
		if(val[mid] > u){
			hi = mid-1;
		} else {
			lo = mid+1;
		}
	}
	return hi;
}

void build(int p, int L, int R){
	if(L==R){
		segtree[p] = L;
		return;
	}
	int M = (L+R)/2;
	build(2*p, L, M);
	build(2*p+1, M+1, R);
	segtree[p] = segtree[2*p];
}

int update(int p, int L, int R, int S, int T, long long v) {

	if(R < S || T < L) {
		return segtree[p];
	}
	if(S <= L && R <= T){
		tot[segtree[p]] = v;
		return segtree[p];
	}
	int M = (L+R)/2;
	int left = update(2*p, L, M, S, T, v);
	int right = update(2*p+1, M+1, R, S, T, v);

	if(left == -1) segtree[p] = right;
	else if(right == -1) segtree[p] = left;
	else segtree[p] = (tot[left] > tot[right] ? left : right);
	return segtree[p];
}

int rmq(int p, int L, int R, int S, int T){
	if(R < S || T < L) {
		return -1;
	}
	if(S <= L && R <= T){
		return segtree[p];
	}
	int M = (L+R)/2;
	int left = rmq(2*p, L, M, S, T);
	int right = rmq(2*p+1, M+1, R, S, T);
	if(left == -1) return right;
	else if(right == -1) return left;
	return (tot[left] > tot[right] ? left : right);
}

void printout(int u){
	if(par[u] == -1){
		printf("%d", u+1);
		return;
	}
	printout(par[u]);
	printf(" %d", u+1);
}

int main(){
	scanf("%d%d", &n,&d);
	long long u;
	for(int i=0;i<n;++i){
		scanf("%I64d", &u);
		val.push_back(u);
		st.push_back(make_pair(u,i));
	}
	if(d==0){
		printf("%d\n", n);
		for(int i=1;i<=n;++i){
			if(i!=1)printf(" ");
			printf("%d",i);
		}
		printf("\n");
		return 0;
	}
	sort(val.begin(), val.end());
	int it = 0;
	while(it+1 < val.size()){
		if(val[it] == val[it+1]) val.erase(val.begin()+it);
		else ++it;
	}
	memset(par, -1, sizeof par);
	N = val.size();
	int ans = -1;
	int maxans = 0;
	build(1, 0, N-1);
	for(int i=0;i<n;++i){
		int cur = lowerbound(st[i].first);
		assert(st[i].first == val[cur]);
		int tmp = 1;
		idx[cur] = st[i].second;
		int k = upperbound(st[i].first-d);
		if(k >= 0){
			int p = rmq(1,0,N-1,0,k);
			if(tot[p]+1 > tmp){
				par[idx[cur]] = idx[p];
				tmp = tot[p] + 1;
			}
		}
		k = lowerbound(st[i].first+d);
		if(k < N){
			int p = rmq(1,0,N-1,k,N-1);
			if(tot[p]+1 > tmp){
				par[idx[cur]] = idx[p];
				tmp = tot[p] + 1;
			}
		}
		if(maxans < tmp){
			ans = idx[cur];
			maxans = tmp;
		}
		update(1,0,N-1,cur,cur,tmp);

	}
	printf("%d\n", maxans);
	printout(ans);
	printf("\n");
	return 0;
}