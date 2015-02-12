#include <cstdio>
#include <algorithm>
using namespace std;
//dp[i][j][e][c1][c2] : maximum  [...] + c1(s[j-1]-s[j]) + c2(s[j]-s[j+1]), e is a flag whether s[j] is currently empty
int dp[30003][203][2][2][2];
int inf = (int) 400000000;
int N, K;
int a[30003];
int s[2] = {1,-1};
int main(){
	scanf("%d%d",&N,&K);
	for(int i=1;i<=N;++i){
		scanf("%d",&a[i]);
	}
	for(int i=0;i<=N+1;++i){
		for(int j=0;j<=K+1;++j){
			for(int e=0;e<2;++e){
				for(int c1=0;c1<2;++c1){
					for(int c2=0;c2<2;++c2){
						dp[i][j][e][c1][c2] = -inf;
						//base case: j is 0 (no subarrays yet)
						if(j==0 && e==0){
							dp[i][j][e][c1][c2] = 0;
						}
					}
				}
			}
		}
	}
	int ans = -inf;
	for(int i=0;i<N;++i){
		for(int j=0;j<=K;++j){
			for(int e=0;e<2;++e){
				for(int c1=0;c1<2;++c1){
					for(int c2=0;c2<2;++c2){
						if(dp[i][j][e][c1][c2]==-inf)continue;
						if(j==0){
							// start a sub array using current a[i+1].
							// hence a[i+1] is in s[1], e = 1
							// c1(0 - s[1]) + c2(s[1] - s[2]) + x (s[2] - s[3]) + ...
							// ^----------^ => 0
							dp[i+1][j+1][1][c1][c2] = max(dp[i+1][j+1][1][c1][c2], s[c2] * a[i+1]);
							// otherwise, don't start a new sub array. 
						} else if (j <= K-1) {
							// we have c1(s[j-1] - s[j]) + c2(s[j] - s[j+1]) + ...
							// currently considering a[i+1].
							// insert a[i+1] to s[j]
							dp[i+1][j][1][c1][c2]  = max(dp[i+1][j][1][c1][c2], (j==1?0:-s[c1]*a[i+1]) + s[c2]*a[i+1] + dp[i][j][e][c1][c2]);
							// s[j] still empty, can not pick a[i+1] to s[j]
							if(e==0) dp[i+1][j][e][c1][c2] = max(dp[i+1][j][e][c1][c2], dp[i][j][e][c1][c2]);
							// ifs[j] is not empty, create new s[j+1], empty or not empty
							if(e!=0){
								for(int x=0;x<2;++x){
									//empty
									dp[i+1][j+1][0][c2][x] = max(dp[i+1][j+1][0][c2][x], dp[i][j][e][c1][c2]);
									// not empty, a[i+1] belongs to s[j+1]
									// c1(s[j-1] - s[j]) + c2(s[j] - s[j+1]) + c3(s[j+1] - s[j+1])
									dp[i+1][j+1][1][c2][x] = max(dp[i+1][j+1][1][c2][x], -s[c2]*a[i+1] + (j==K-1?0:s[x]*a[i+1]) + dp[i][j][e][c1][c2]);
								}
							}
						} else if (j == K) {
							// can insert a[i+1] to current s[j]
							dp[i+1][j][1][c1][c2]  = max(dp[i+1][j][1][c1][c2], -s[c1]*a[i+1] + dp[i][j][e][c1][c2]);
							// s[j] still empty, not pick a[i+1] to s[j]
							if(e==0)dp[i+1][j][e][c1][c2] = max(dp[i+1][j][e][c1][c2], dp[i][j][e][c1][c2]);
						}
					}
				}
			}
		}
	}
	for(int i=0;i<=N;++i){
		for(int c1=0;c1<2;++c1){
			for(int c2=0;c2<2;++c2){
				ans = max(ans,dp[i][K][1][c1][c2]);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}