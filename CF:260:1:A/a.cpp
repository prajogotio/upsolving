#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int cnt[100005];
long long dp[100005][2];
int N;
int main(){
	int u;
	scanf("%d", &N);
	for(int i=0;i<N;++i){
		scanf("%d",&u);
		cnt[u]++;
	}
	long long ans = 0;
	for(int i=0;i<100000;++i){
		dp[i][1] = 1LL*cnt[i+1]*(i+1);
		if(i>0){
			//dont take i
			dp[i][0] = max(dp[i-1][0],dp[i-1][1]);
		}
		if(i>1){
			//take i
			dp[i][1] += max(dp[i-1][0],max(dp[i-2][1],dp[i-2][0]));
		}
		ans = max(dp[i][0],dp[i][1]);
	}
	cout << ans << endl;
}