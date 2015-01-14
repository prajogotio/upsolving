#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int st[800003];
int a[200003], b[200003];
int p[200003], q[200003];
int N;

void reset_st(int p=1, int L=0, int R=N-1){
	if(L==R){
		st[p] = 1;
		return;
	}
	int M = (L+R)/2;
	reset_st(2*p,L,M);
	reset_st(2*p+1,M+1,R);
	st[p] = st[2*p]+st[2*p+1];
}

void delete_elem(int S,int p=1,int L=0,int R=N-1){
	if(R<S || S<L)return;
	if(L==R && R==S){
		st[p] = 0;
		return;
	}
	int M=(L+R)/2;
	delete_elem(S,2*p,L,M);
	delete_elem(S,2*p+1,M+1,R);
	st[p] = st[2*p]+st[2*p+1];
}

int rmq(int S,int T,int p=1,int L=0,int R=N-1){
	if(R<S||T<L)return -1;
	if(S<=L && R<=T)return st[p];
	int M=(L+R)/2;
	int left = rmq(S,T,2*p,L,M);
	int right = rmq(S,T,2*p+1,M+1,R);
	if(left == -1)return right;
	if(right == -1)return left;
	return left+right;
}

int find(int pos,int p=1,int L=0,int R=N-1){
	if(L==R){
		return L;
	}
	int M=(L+R)/2;
	int left = rmq(L,M,2*p,L,M);
	if(pos-left > 0){
		return find(pos-left,2*p+1,M+1,R);
	} else {
		return find(pos,2*p,L,M);
	}
}

int main(){
	scanf("%d",&N);
	for(int i=0;i<N;++i){
		scanf("%d",&a[i]);
	}
	for(int i=0;i<N;++i){
		scanf("%d",&b[i]);
	}
	reset_st();
	for(int i=0;i<N;++i){
		p[i] = rmq(0,a[i])-1;
		delete_elem(a[i]);
	}
	reset_st();
	for(int i=0;i<N;++i){
		q[i] = rmq(0,b[i])-1;
		delete_elem(b[i]);
	}
	for(int i=0;i<N;++i){
		p[i] += q[i];
	}
	for(int i=N-1;i>=0;--i){
		int k = N-i-1;
		if(p[i]>k){
			if(i!=0)p[i-1]++;
			p[i] -= k+1;
		}
	}
	reset_st();
	for(int i=0;i<N;++i){
		if(i!=0)printf(" ");
		int k = find(p[i]+1);
		printf("%d", k);
		delete_elem(k);
	}
	printf("\n");
	return 0;
}