#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <iostream>
using namespace std;


int R[1000003], to_left[1000003], to_right[1000003], L[1000003];
vector<int> S;
int N, C;
bool ok;

int build(int from, int to) {
	printf("%d,%d\n",from,to);
	if(!ok)return 0;
	// termination/base case
	if(from > to) {
		return 0;
	}

	// nodes rooted at from, having nodes in [from+1, to]
	// returns minimum number of nodes in this subtree
	// invariant: to - from + 1 is the max number of nodes.

	// if there is no left constraint, place all to the right
	if(!to_left[from] && to_right[from]) {
		if(R[from] > to) return 0;
		S.push_back(from);
		return 1 + build(from+1, to);
	}

	// else if there is no right constraint, place all to the left
	if(!to_right[from] && to_left[from]) {
		if(L[from] > to) return 0;
		int ret = 1 + build(from+1,to);
		S.push_back(from);
		return ret;
	}

	if(!to_right[from] && !to_left[from]) {
		S.push_back(from);
		return 1 + build(from+1,to);
	}

	// else, there is constraint on both sides
	// divide into two
	// from -> (from+1, mid), (mid+1, to)
	// mid < R[from] or else it is not consistent
	if(R[from]>to || from+1>R[from]) return 0;
	if(L[from]>to || from+1>L[from]) return 0;
	if(R[from] < L[from]) {
		ok = false;
		return 0; 
	}
	if(from==to){
		S.push_back(from);
		return 1;
	}

	int m = build(from+1, R[from]-1);
	if(m+from>=R[from]) {
		ok = false;
		return 0;
	}
	S.push_back(from);
	int n = build(from+m+1, to);
	// checking for invariant
	if(from+n>to) {
		ok = false;
		return 0;
	}
	return n+m+1;
}


int main(){
	int u,v;
	string type;
	scanf("%d%d",&N,&C);
	for(int i=1;i<=N;++i){
		R[i] = N+1;
	}
	ok = true;
	for(int i=0;i<C;++i){
		scanf("%d%d",&u,&v);
		cin>>type;
		if(v <= u) {
			ok = false;
			break;
		}
		if(type == "RIGHT"){
			R[u] = min(R[u],v);
			to_right[u] = 1;
		}
		else {
			to_left[u] = 1;
			L[u] = max(L[u],v);
		}
	}
	build(1, N);
	if(ok){
		for(int i=0;i<N;++i){
			if(i!=0)printf(" ");
			printf("%d",S[i]);
		}
		printf("\n");
	} else {
		printf("IMPOSSIBLE\n");
	}
	return 0;
}