#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;

int segtree[400005][60];
int vis[400005][60];
int a[100005];
int N, Q;
int iter;
int build(int p, int t, int L, int R){
	if(vis[p][t%60]) return segtree[p][t%60];
	vis[p][t%60] = 1;
	if(L==R){
		segtree[p][t%60] = 1;
		if(t%a[L] == 0) segtree[p][t%60]++;
		return segtree[p][t%60];
	}
	int M = (L+R)/2;
	int left = build(2*p,t,L,M);
	int right = build(2*p+1,t+left,M+1,R);
	segtree[p][t%60] = left+right;
	build(2*p+1,t,M+1,R);
	return left+right;
}

int rmq(int p,int t,int L,int R,int S,int T){
	if(T<L||R<S)return t;
	if(S<=L&&R<=T){
		return t + segtree[p][t%60];
	}
	int M=(L+R)/2;
	int left = rmq(2*p,t,L,M,S,T);
	int right = rmq(2*p+1,left,M+1,R,S,T);
	return right;
}
/*
int update(int p, int t, int L, int R, int S){
	if(vis[p][t%60]==iter)return segtree[p][t%60];
	vis[p][t%60] = iter;
	if(R<S||S<L)return segtree[p][t%60];
	if(R==L && L==S){
		segtree[p][t%60] = 1;
		if(t%a[L]==0)segtree[p][t%60]++;
		return segtree[p][t%60];
	}
	int M=(L+R)/2;
	int left=update(2*p,t,L,M,S);
	int right=update(2*p+1,t+left,M+1,R,S);
	segtree[p][t%60]=left+right;
	update(2*p+1,t,M+1,R,S);
	return segtree[p][t%60];
}
*/
void update(int p, int L, int R, int S){
	if(R<S||S<L)return;
	if(R==L && L==S){
		for(int i=0;i<60;++i){
			segtree[p][i] = (i%a[L]==0 ? 2: 1);
		}
		return;
	}
	int M=(L+R)/2;
	update(2*p,L,M,S);
	update(2*p+1,M+1,R,S);
	for(int i=0;i<60;++i){
		int left = segtree[2*p][i];
		segtree[p][i] = segtree[2*p][i] + segtree[2*p+1][(i+left)%60];
	}
}

int main(){
	int x,y;
	char c;
	scanf("%d", &N);
	for(int i=0;i<N;++i){
		scanf("%d", &a[i]);
	}
	for(int i=0;i<60;++i){
		build(1,i,0,N-1);
	}
	scanf("%d",&Q);
	iter = 1;
	for(int qq=0;qq<Q;++qq){
		scanf(" %c%d%d", &c,&x,&y);
		if(c=='C'){
			a[x-1]=y;
			update(1,0,N-1,x-1);
		} else {
			printf("%d\n",rmq(1,0,0,N-1,x-1,y-2));
		}
	}
	return 0;
}