#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int INF = (int) 1e9;
int segtree[2000003];
int a[500003];
int c[500003];
int linklist[500003][2];
int N;

// WRONG STRATEGY

int decider(int i, int j) {
	if(c[i] == 0) return j;
	if(c[j] == 0) return i;
	if(a[i] == a[j]) {
		if(c[i] < c[j]) return j;
		else return i;
	}
	if(a[i] < a[j]) return i;
	else return j;
}

void build(int p, int L, int R) {
	if(L==R) {
		segtree[p] = L;
		return;
	}
	int M = (L+R)/2;
	build(2*p, L, M);
	build(2*p+1, M+1, R);
	segtree[p] = decider(segtree[2*p], segtree[2*p+1]);
}

int rmq(int p, int S, int T, int L, int R) {
	if(T<L || R<S) return -1;
	if(S<=L && R<=T) {
		return segtree[p];
	}
	int M = (L+R)/2;
	int left = rmq(2*p, S, T, L, M);
	int right = rmq(2*p+1, S, T, M+1, R);
	if(left==-1)return right;
	if(right==-1)return left;
	return decider(left, right);
}

void update(int p, int S, int L, int R) {
	if(S<L || R<S)return;
	if(S==L && L==R){
		return;
	}
	int M=(L+R)/2;
	update(2*p,S,L,M);
	update(2*p+1,S,M+1,R);
	segtree[p] = decider(segtree[2*p], segtree[2*p+1]);
}

void init() {
	for(int i=0;i<N;++i){
		c[i] = INF;
		if(i > 0) {
			c[i] = min(c[i], a[i-1]);
			linklist[i][0] = i-1;
		} else {
			c[i] = 0;
			linklist[i][0] = -1;
		}
		if(i+1 < N) {
			c[i] = min(c[i], a[i+1]);
			linklist[i][1] = i+1;
		} else {
			c[i] = 0;
			linklist[i][1] = -1;
		}
	}
	build(1,0,N-1);
}

int main(){ 
	scanf("%d",&N);
	for(int i=0;i<N;++i){
		scanf("%d",&a[i]);
	}
	init();
	long long ans = 0;
	for(int qq=0;qq<N-2;++qq) {
		int i = rmq(1, 0, N-1, 0, N-1);
		printf("c[%d] = %d\n", i, c[i]);
		ans += c[i];
		c[i] = 0;
		update(1, i, 0, N-1);
		int left = linklist[i][0];
		int right = linklist[i][1];
		linklist[left][1] = right;
		linklist[right][0] = left;
		if(left != 0){
			c[left] = min(a[linklist[left][0]], a[linklist[left][1]]);
			//printf("left: c[%d] = %d\n", left, c[left]);
			update(1, left, 0, N-1);
		}
		if(right != N-1) {
			c[right] = min(a[linklist[right][0]], a[linklist[right][1]]);
			//printf("right: c[%d] = %d\n", right, c[right]);
			update(1, right, 0, N-1);
		}
	}
	cout << ans << endl;
	return 0;
}