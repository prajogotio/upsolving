#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

long long MOD = (long long) 1e9 + 7LL;
int t,k;
long long dp[100005];
long long sum[100005];
int main(){
	scanf("%d%d", &t,&k);
	for(int i=0;i<k;++i){
		dp[i] = 1;
	}
	for(int i=k;i<=100000;++i){
		dp[i] = (dp[i-1] + dp[i-k]) % MOD;
	}
	for(int i=0;i<=100000;++i){
		sum[i] = dp[i];
		if(i>0) sum[i] += sum[i-1];
		sum[i] %= MOD;
	}
	int u,v;
	for(int tc=0;tc<t;++tc){
		scanf("%d %d", &u,&v);
		long long tmp = sum[v];
		if(u > 0) tmp -= sum[u-1];
		if(tmp < 0) tmp += MOD;
		cout << tmp << endl;
	}
	return 0;

}