#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
double dp[110][110][110];
int vis[110][110][110];
int r, s, p;

struct pt {
	int i,j,k;
	pt(int x, int y, int z):i(x),j(y),k(z){}
};

void enq(queue<pt> &q, int i, int j, int k){
	if (i < 0 || j < 0 || k < 0) return;
	if (vis[i][j][k]) return;
	q.push(pt(i,j,k));
	vis[i][j][k] = 1;
}

int main() {
	scanf("%d%d%d",&r,&s,&p);
	dp[r][s][p] = 1;
	vis[r][s][p] = 1;
	queue<pt> q;
	q.push(pt(r,s,p));
	while(!q.empty()){
		int i = q.front().i;
		int j = q.front().j;
		int k = q.front().k;
		q.pop();
		double den = i*j + j*k + k*i;
		if(i>0 && j>0) dp[i][j-1][k] += dp[i][j][k] * ((double)(i*j)/den);
		if(i>0 && k>0) dp[i-1][j][k] += dp[i][j][k] * ((double)(i*k)/den);
		if(j>0 && k>0) dp[i][j][k-1] += dp[i][j][k] * ((double)(j*k)/den);
		enq(q,i,j-1,k);
		enq(q,i,j,k-1);
		enq(q,i-1,j,k);
	}
	for(int i=max(r,max(s,p));i>1;--i) {
		dp[i-1][0][0] += dp[i][0][0];
		dp[0][i-1][0] += dp[0][i][0];
		dp[0][0][i-1] += dp[0][0][i];
	}
	printf("%.12lf %.12lf %.12lf\n", dp[1][0][0], dp[0][1][0], dp[0][0][1]);
	return 0;
}