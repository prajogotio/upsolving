#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;



long long dp[2][510][510];
int n, m, b;
long long mod;
int a[510];

int main(){
	cin >> n >> m >> b >> mod;
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	dp[1][m][0] = 1;
	for(int i=1;i<=n;++i){
		int cur = i % 2;
		int next = (i+1) % 2;
		for(int t=0;t<=m;++t){
			for(int k=0;k<=b;++k){
				dp[next][t][k] = 0;
			}
		}
		for(int t=m;t>=0;--t){
			for(int k=0;k<=b;++k){
				dp[next][t][k] += dp[cur][t][k];
				dp[next][t][k] %= mod;
				if(t>0 && k+a[i]<=b) {
					dp[cur][t-1][k+a[i]] += dp[cur][t][k];
					dp[cur][t-1][k+a[i]] %= mod;
				}
			}
		}
	}
	long long ans = 0;
	for(int i=0;i<=b;++i){
		ans += dp[n%2][0][i];
		ans %= mod;
	}
	cout << ans << endl;
	return 0;
}