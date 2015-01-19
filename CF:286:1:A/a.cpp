#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <utility>
#include <string>
using namespace std;

int dp[603][30003];
int mark[30003];
int N, D;
int Z = 299;
int main(){
	int u;
	scanf("%d %d",&N,&D);
	for(int i=0;i<N;++i){
		scanf("%d",&u);
		mark[u]++;
	}
	for(int i=30000;i>=0;--i){
		for(int k=0;k<=600;++k){
			dp[k][i] = mark[i];
			int cur = D+k-Z;
			if(cur<1)continue;
			if(i+cur<=30000){
				dp[k][i] = max(dp[k][i],dp[k][i+cur]+mark[i]);
			}
			if(i+cur+1<=30000 && k!=600){
				dp[k][i] = max(dp[k][i],dp[k+1][i+cur+1]+mark[i]);
			}
			if(i+cur-1<=30000 && cur != 1){
				dp[k][i] = max(dp[k][i],dp[k-1][i+cur-1]+mark[i]);
			}
		}
	}
	printf("%d\n",dp[Z][D]);
	return 0;
}