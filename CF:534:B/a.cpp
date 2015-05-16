#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int dp[1110][1110];

int v[2], t, d;

int main(){
	scanf("%d%d%d%d",&v[0],&v[1],&t,&d);
	for(int i=0;i<1110;++i)
		for(int j=0;j<1110;++j)
			dp[i][j]=-12345678;
	dp[0][v[0]]=0;
	for(int i=0;i<t-1;++i){
		for(int j=0;j<=1100;++j){
			if(dp[i][j]<0)continue;
			for(int k=0;k<=d;++k){
				if(j-k>=0) dp[i+1][j-k] = max(dp[i][j]+j, dp[i+1][j-k]);
				if(j+k<=1100) dp[i+1][j+k] = max(dp[i][j]+j, dp[i+1][j+k]);
			}
		}
	}
	printf("%d\n",dp[t-1][v[1]]+v[1]);
	return 0;
}