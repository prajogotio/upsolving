#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

long long sum[5003];
long long dp[5003][5003];
int M,N,K;

int main(){
	int u;
	scanf("%d%d%d",&N,&M,&K);
	sum[0] = 0;
	for(int i=1;i<=N;++i){
		scanf("%d",&u);
		sum[i] = sum[i-1] + u;
	}
	long long ans = 0;
	for(int k=1;k<=K;++k){
		for(int i=1;i<=N;++i){
			dp[k-1][i] = max(dp[k-1][i], dp[k-1][i-1]);
		}
		for(int i=N;i>=M;--i){
			dp[k][i] = dp[k-1][i-M] + sum[i] - sum[i-M];
			if(k==K)ans = max(dp[k][i], ans);
		}
	}
	cout << ans << endl;
	return 0;
}