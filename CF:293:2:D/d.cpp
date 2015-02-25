#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#include <set>
#include <string>
using namespace std;


int N, T;
double P;
double dp[2003][2003];
int main(){

	scanf("%d%lf%d",&N,&P,&T);
	for(int n=0;n<=N;++n){
		for(int t=0;t<=T;++t){
			dp[n][t]=0;
		}
	}
	dp[0][0] = 1;
	for(int n=0;n<=N;++n){
		for(int t=0;t<=T;++t){
			dp[n][t+1] += dp[n][t] * (n == N ? 1.0 : (1.0-P));
			dp[n+1][t+1] += dp[n][t] * P;
		}
	}
	// for(int n=0;n<=N;++n){
	// 	for(int t=0;t<=T;++t){
	// 		printf("%.5lf ",dp[n][t]);
	// 	}
	// 	printf("\n");
	// }
	double ans = 0;
	for(int n=0;n<=N;++n){
		ans += n * dp[n][T];
	}
	printf("%.12lf\n",ans);
	return 0;
}