#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
using namespace std;
int N;
int segtree[1000000];
pair<int,int> d[200003];

/* WEIRD... */


int bsearch(int val){
	int lo = 0, hi = N-1, mid;
	while(lo <= hi){
		mid = (lo+hi)/2;
		if(d[mid].first == val) return mid;
		if(d[mid].first < val){
			lo = mid+1;
		} else {
			hi = mid-1;
		}
	}
	return hi;
}

int rmq(int p, int L, int R, int S, int T){
	if(T < L || R < S) return -1;
	if(S <= L && R <= T){
		return segtree[p];
	}
	int M = (L+R)/2;
	int left = rmq(2*p, L, M, S, T);
	int right = rmq(2*p+1, M+1, R, S, T);
	if(left < 0) return right;
	if(right < 0) return left;
	int val = d[M].second;
	int idx = bsearch(val);
	if(idx == M){
		return left + right + d[M+1].first - d[M].second - 1;
	} else {
		int diff = 0;
		if(d[idx].first != val && idx < N-1){
			diff = rmq(2*p+1, M+1, R, M+1, idx+1) - rmq(2*p+1, M+1, R, M+1, idx);
			diff = min(diff, d[idx+1].first - d[M].second - 1);
		}
		diff += rmq(2*p+1, M+1, R, M+1, idx);
		return left + right - diff;
	}
}

void build(int p, int L, int R){
	if(L==R){
		segtree[p] = 0;
		return;
	}
	int M = (L+R)/2;
	build(2*p, L, M);
	build(2*p+1, M+1, R);
	int val = d[M].second;
	int idx = bsearch(val);
	if(idx == M){
		segtree[p] = segtree[2*p] + segtree[2*p+1] + d[M+1].first - d[M].second - 1;
	} else {
		int diff = 0;
		if(d[idx].first != val && idx < N-1){
			diff = rmq(2*p+1, M+1, R, M+1, idx+1) - rmq(2*p+1, M+1, R, M+1, idx);
			diff = min(diff, d[idx+1].first - d[M].second - 1);
		}
		diff += rmq(2*p+1, M+1, R, M+1, idx);
		segtree[p] = segtree[2*p] + segtree[2*p+1] - diff;
	}
	//printf("[%d,%d][%d] = %d\n", L,R,p,segtree[p]);
}

int main(){
	int u,v;
	scanf("%d", &N);
	for(int i=0;i<N;++i){
		scanf("%d%d", &u,&v);
		d[i] = make_pair(u,v+u-1);
	}
	build(1,0,N-1);
	int M;
	scanf("%d", &M);
	for(int i=0;i<M;++i){
		scanf("%d%d", &u,&v);
		printf("%d\n", rmq(1,0,N-1,u-1,v-1));
	}
	return 0;
}