#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
using namespace std;


// STILL WRONG, NVM REDO


pair<int,int> d[200003];
int segtree[1000000];
int offset[1000000];
int N, M;

int lowerbound(int val){
	int lo=0,hi=N-1,mid;
	while(lo<=hi){
		mid=(lo+hi)/2;
		if(d[mid].first < val){
			lo = mid+1;
		} else {
			hi = mid-1;
		}
	}
	return lo;
}

pair<int,int> rmq(int p, int L, int R, int S, int T){
	if(R<S || T<L) return make_pair(-1,-1);
	if(S<=L && R<=T){
		return make_pair(segtree[p],offset[p]);
	}
	int M = (L+R)/2;
	pair<int,int> left = rmq(2*p,L,M,S,T);
	pair<int,int> right = rmq(2*p+1,M+1,R,S,T);
	if(left.first<0)return right;
	if(right.first<0)return left;
	int idx = lowerbound(left.second);
	if(idx == M+1){

		return make_pair(left.first + right.first + d[M+1].first - left.second - 1,
						max(left.second, right.second));
	} else {
		pair<int,int> diff;
		if(left.second != d[idx].first) diff = rmq(2*p+1,M+1,R,M+1,idx-1);
		else diff = rmq(2*p+1,M+1,R,M+1,idx);
		int tmp = 0;
		if(left.second > diff.second) {
			tmp = left.second - diff.second;
		}
		return make_pair(left.first + right.first - diff.first - tmp,
						max(left.second, right.second));
	}
}

void build(int p, int L, int R, int S, int T){
	if(L==R){
		segtree[p] = 0;
		offset[p] = d[L].second;
		return;
	}
	int M = (L+R)/2;
	build(2*p,L,M,S,T);
	build(2*p+1,M+1,R,S,T);
	offset[p] = max(offset[2*p], offset[2*p+1]);
	int idx = lowerbound(offset[2*p]);
	if(idx == M+1){
		segtree[p] = segtree[2*p] + segtree[2*p+1] + d[M+1].first - offset[2*p] - 1;
	} else {
		pair<int,int> diff;
		if(d[idx].first != offset[2*p]) diff = rmq(2*p+1,M+1,R,M+1,idx-1);
		else diff = rmq(2*p+1,M+1,R,M+1,idx);
		int tmp = 0;
		if(offset[2*p] > diff.second) {
			tmp = offset[2*p] - diff.second;
		}
		segtree[p] = segtree[2*p] + segtree[2*p+1] - diff.first - tmp;
	}
}

int main(){
	int u,v;
	scanf("%d", &N);
	for(int i=0;i<N;++i){
		scanf("%d%d", &u,&v);
		d[i] = make_pair(u,u+v);
	}
	scanf("%d", &M);
	for(int i=0;i<M;++i){
		scanf("%d%d", &u,&v);
		pair<int,int> ret = rmq(1,0,N-1,u-1,v-2);
	}
	return 0;
}