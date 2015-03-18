#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <set>
using namespace std;

int maxtree[4][1000000];
int mintree[2][1000000];
int mark[2][200005];
int N[2], Q;

void init() {
	for(int i=0;i<200005;++i)mark[0][i] = mark[1][i] = 0;
	for(int i=0;i<4;++i){
		for(int j=0;j<1000000;++j){
			maxtree[i][j] = -1;
		}
	}
	for(int i=0;i<2;++i){
		for(int j=0;j<1000000;++j){
			mintree[i][j] = 12345678;
		}
	}
}

void updateMax(int tree[][1000000], int i, int p, int S, int L, int R, int val) {
	if(S < L || R < S) return;
	if(L==R && R==S) {
		if(val == 1){
			tree[i][p] = L;
		} else if(val ==0){
			tree[i][p] = -1;
		}
		return;
	}
	int M = (L+R)/2;
	updateMax(tree, i, 2*p, S, L, M, val);
	updateMax(tree, i, 2*p+1, S, M+1, R, val);
	tree[i][p] = max(tree[i][2*p], tree[i][2*p+1]);
}

void updateMin(int tree[][1000000], int i, int p, int S, int L, int R, int val) {
	if(S < L || R < S) return;
	if(L==R && R==S) {
		if(val == 1){
			tree[i][p] = L;
		} else if(val ==0){
			tree[i][p] = 12345678;
		}
		return;
	}
	int M = (L+R)/2;
	updateMin(tree, i, 2*p, S, L, M, val);
	updateMin(tree, i, 2*p+1, S, M+1, R, val);
	tree[i][p] = min(tree[i][2*p], tree[i][2*p+1]);
}

int getMax(int tree[][1000000], int i, int p, int S, int T, int L, int R) {
	if(T < L || R < S) return -1;
	if(S <= L && R <= T) return tree[i][p];
	int M = (L+R)/2;
	int left = getMax(tree, i, 2*p, S, T, L, M);
	int right = getMax(tree, i, 2*p+1, S, T, M+1, R);
	return max(left, right);
}

int getMin(int tree[][1000000], int i, int p, int S, int T, int L, int R) {
	if(T < L || R < S) return 12345678;
	if(S <= L && R <= T) return tree[i][p];
	int M = (L+R)/2;
	int left = getMin(tree, i, 2*p, S, T, L, M);
	int right = getMin(tree, i, 2*p+1, S, T, M+1, R);
	return min(left, right);
}

void setVal(int i, int pos) {
	updateMax(maxtree, i, 1, pos, 0, N[i], 1);
	updateMin(mintree, i, 1, pos, 0, N[i], 1);
}

void handleCut(int i, int pos) {
	int left = getMax(maxtree, i, 1, 0, pos-1, 0, N[i]);
	int right = getMin(mintree, i, 1, pos+1, N[i], 0, N[i]);
	int len = right-left;
	mark[i][len]--;
	setVal(i, pos);
	if(mark[i][len]==0){
		updateMax(maxtree,i+2,1,len,0,N[i],0);
	}
	mark[i][pos-left]++;
	if(mark[i][pos-left]==1)updateMax(maxtree,i+2,1,pos-left,0,N[i],1);
	mark[i][right-pos]++;
	if(mark[i][right-pos]==1)updateMax(maxtree,i+2,1,right-pos,0,N[i],1);
}

void printMaxArea() {
	int maxW = getMax(maxtree, 2, 1, 0, N[0], 0, N[0]);
	int maxH = getMax(maxtree, 3, 1, 0, N[1], 0, N[1]);
	printf("%I64d\n",1LL*maxW * maxH);
}


int main(){
	scanf("%d%d%d",&N[0],&N[1], &Q);
	init();
	setVal(0, 0);
	setVal(0, N[0]);
	setVal(1, 0);
	setVal(1, N[1]);
	updateMax(maxtree, 2, 1, N[0], 0, N[0], 1);
	mark[0][N[0]]++;
	updateMax(maxtree, 3, 1, N[1], 0, N[1], 1);
	mark[1][N[1]]++;

	for(int qq=0;qq<Q;++qq){
		char c;
		int d;
		cin>>c>>d;
		if(c == 'H') {
			handleCut(1, d);
		} else {
			handleCut(0, d);
		}
		printMaxArea();
	}
	return 0;
}