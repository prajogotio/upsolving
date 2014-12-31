#include <iostream>
#include <algorithm>
#include <utility>
#include <cstdio>
#include <cassert>
using namespace std;

int N, M;
pair<long long,long long> edge[200003];
pair<long long,long long> segtree[1000003];

int lowerbound(long long val){
	int lo=0,hi=N-1,mid;
	while(lo<=hi){
		mid=(lo+hi)/2;
		if(edge[mid].first < val){
			lo=mid+1;
		} else {
			hi=mid-1;
		}
	}
	return lo;
}

pair<long long,long long> rmq(int p,int L,int R,int S,int T){
	if(R<S||T<L)return make_pair(-1,-1);
	if(S<=L&&R<=T){
		return segtree[p];
	}
	int M=(L+R)/2;
	pair<long long,long long> left=rmq(2*p,L,M,S,T);
	pair<long long,long long> right=rmq(2*p+1,M+1,R,S,T);
	if(left.first==-1)return right;
	if(right.first==-1)return left;
	pair<long long,long long> ret = make_pair(0,max(left.second,right.second));
	int idx = lowerbound(left.second+1);
	if(idx>min(R,T)){
		ret.first = left.first;
	}else if(idx == M+1){
		ret.first = left.first + right.first + edge[M+1].first - left.second - 1;
	} else {
		pair<long long,long long> tmp = rmq(2*p+1,M+1,R,M+1,idx-1);
		if(left.second > tmp.second){
			tmp.first += left.second - tmp.second;
		}
		ret.first = left.first + right.first - tmp.first;
		assert(ret.first >= left.first);
	}
	assert(ret.first>=0);
	return ret;
}

void build(int p,int L,int R){
	if(L==R){
		segtree[p] = make_pair(0,edge[L].second);
		return;
	}
	int M=(L+R)/2;
	build(2*p,L,M);
	build(2*p+1,M+1,R);
	segtree[p].second = max(segtree[2*p].second, segtree[2*p+1].second);
	int idx = lowerbound(segtree[2*p].second+1);
	if(idx>R) {
		segtree[p].first = segtree[2*p].first;
	}else if(idx == M+1){
		segtree[p].first = segtree[2*p].first + segtree[2*p+1].first + edge[M+1].first - segtree[2*p].second - 1;
	} else {
		pair<long long,long long> ret = rmq(2*p+1,M+1,R,M+1,idx-1);
		if(segtree[2*p].second > ret.second){
			ret.first += segtree[2*p].second - ret.second;
		}
		segtree[p].first = segtree[2*p].first + segtree[2*p+1].first - ret.first;
	}
	assert(segtree[p].first>=0);
}

int main(){
	int u,v;
	scanf("%d", &N);
	for(int i=0;i<N;++i){
		scanf("%d%d",&u,&v);
		edge[i] = make_pair(u,(long long)u+v-1LL);
	}
	build(1,0,N-1);
	scanf("%d", &M);
	for(int i=0;i<M;++i){
		scanf("%d%d", &u,&v);
		printf("%I64d\n",rmq(1,0,N-1,u-1,v-1).first);
	}
	return 0;
}