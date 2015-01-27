#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

long long dp[1003][103];
long long ways[1003];
int N;
long long K, MOD;
int main(){
	scanf("%d",&N);
	cin >> K;
	cin >> MOD;
	long long pow10 = 1;
	for(int i=N;i>=1;--i){
		for(int j=0;j<10;++j){
			if(i == 1 && j == 0) continue;
			long long val = (pow10 * j)%K;
			if(i == N){
				dp[i][(int)val]++;
				dp[i][(int)val]%= MOD;
				if(val==0 && j != 0) {
					ways[i]++;
					ways[i] %= MOD;
				}
				continue;
			}
			for(int k=1;k<K;++k){
				dp[i][(k+(int)val)%K] += dp[i+1][k];
				dp[i][(k+(int)val)%K] %= MOD;
				if(j!= 0 && (k+(int)val)%K==0) {
					ways[i] += dp[i+1][k];
					ways[i] %= MOD;
				}
			}
			dp[i][val%K]++;
			if(j!=0 && val%K==0)ways[i]++;
		}
		pow10 *= 10LL;
		pow10 %= K;
	}
	long long pq = 1;
	long long ans = 0;
	for(int i=1;i<=N;++i){
		ans += ways[i] * pq;
		ans %= MOD;
		if(i==1)pq *= 9LL;
		else pq *= 10LL;
		pq %= MOD;
	}
	cout << ans << endl;
	return 0;
}