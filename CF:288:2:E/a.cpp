#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

/*
	PROBLEM STATEMENT IS NOT TO CLEAR HUH
	CORRESPONDING CLOSING BRACKET MUST BE THE AVAILABLE CLOSING BRACKET CLOSEST TO 
	THE OPENING BRACKET

	D[i][j]: can I build the required structure using i-th to j-th constraints?
	D[i][j] = OR_{all k} [ D[i+1][i+k] & D[i+k+1][j] ]
*/

int N;
int D[603][603];
int L[603], R[603];
int path[603][603];

void print_ans(int i, int j) {
	if(i>j)return;
	if(i==j){
		printf("()");
	} else {
		int m = i+path[i][j];
		printf("(");
		print_ans(i+1,m);
		printf(")");
		print_ans(m+1,j);
	}
}

int main(){
	scanf("%d",&N);
	for(int i=0;i<N;++i){
		scanf("%d%d",&L[i],&R[i]);
	}
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			D[i][j] = 0;
			path[i][j] = -1;
		}
	}
	for(int i=0;i<N;++i){
		D[i][i] = (L[i]==1);
		D[i+1][i] = 1;
	}
	for(int len=1;len<N;++len){
		for(int i=0;i<N;++i){
			int j = i+len;
			if(i+len >= N) break;
			D[i][j] = 0;
			for(int m=L[i];m<=R[i];++m){
				if(!(m%2))continue;
				int k = (m-1)/2;
				if(i+k+1>j+1)continue;
				int cur = D[i+1][i+k] & D[i+k+1][j];
				if(cur){
					D[i][j] = cur;
					path[i][j] = k;
					break;
				}
			}
		}
	}
	if(D[0][N-1]) {
		print_ans(0,N-1);
		printf("\n");
	} else {
		printf("IMPOSSIBLE\n");
	}
	return 0;
}