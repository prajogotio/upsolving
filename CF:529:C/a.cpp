#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

// THOUGH WRONGLY


int row[100005], col[100005];
int r[100005], c[100005];
int N, M, K, Q;

int main(){
	scanf("%d%d%d%d",&N,&M,&K,&Q);
	int x, y;
	for(int i=0;i<K;++i){
		scanf("%d%d",&x,&y);
		r[x] = 1;
		c[y] = 1;
	}
	row[0] = col[0] = 0;
	for(int i=1;i<=N;++i){
		row[i] = row[i-1] + r[i];
	}
	for(int i=1;i<=M;++i){
		col[i] = col[i-1] + c[i];
	}
	int x1,x2,y1,y2;
	for(int qq=0;qq<Q;++qq){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		if(x1>x2)swap(x1,x2);
		if(y1>y2)swap(y1,y2);
		bool ok = (x2-x1+1 == row[x2]-row[x1-1] && y2-y1+1 == col[y2]-col[y1-1]);
		if(ok) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}