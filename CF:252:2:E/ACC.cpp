#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

/*
DP STATE:
dp[i][bm][9th_bit][count] : probability of having bitmask bm with
9th bit equals 9th_bit, and having count bits following 9th_bit equals to 9th_bit

dp[i][bm][9th_bit][count] can move to:
1.	leftshift 2:
	new_bm = bm0 & 255
	if 9th_bit == (bm0) & (1<<8):
   		new_count = count+1
	else 9th_bit = (bm0) & (1<<8)
		 new_count = 0
2.	add 1:
	new_bm = bm + 1
	if new_bm & (1<<8) == 1:
		if 9th_bit == 1, 9th_bit -> 0, new_cnt = cnt
		else 9th_bit = 1, cnt = 0.
	else:
		nochange
*/

int X,K,P;
double dp[203][260][2][260];
int main(){
	scanf("%d%d%d",&X,&K,&P);
	double prob = 0.01*P;
	int bm = X & 255;
	int last = (X>>8) & 1;
	int tmp = X>>8;
	int cnt = 0;
	while(tmp && (tmp&1) == last){
		++cnt;
		tmp >>= 1;
	}
	dp[0][bm][last][cnt] = 1.0;

	for(int k=0;k<K;++k){
		for(int i=0;i<256;++i){
			for(int j=0;j<2;++j){
				for(int cnt=0;cnt<240;++cnt){
					//left shift
					int new_bm = i << 1;
					int new_cnt, new_last;
					if(new_bm & 256) {
						new_last = 1;
						if(j==1) {
							new_cnt = cnt+1;
						} else {
							new_cnt = 1;
						}
					} else {
						new_last = 0;
						if(j==1) {
							new_cnt = 1;
						} else {
							new_cnt = (cnt==0 ? 0 : cnt+1);
						}
					}
					new_bm &= 255;
					dp[k+1][new_bm][new_last][new_cnt] += prob * dp[k][i][j][cnt];
					//add 1
					new_bm = i+1;
					if(new_bm&256) {
						if(j == 1) {
							new_last = 0;
							new_cnt = cnt;
						} else {
							new_last = 1;
							new_cnt = 1;
						}
					} else {
						new_last = j;
						new_cnt = cnt;
					}
					new_bm &= 255;
					dp[k+1][new_bm][new_last][new_cnt] += (1.0 - prob) * dp[k][i][j][cnt];
				}
			}
		}
	}
	double ans = 0;
	for(int i=0;i<256;++i){
		for(int j=0;j<2;++j){
			for(int cnt=0;cnt<240;++cnt){
				int val = 0;
				if(j==1 || i&255) {
					if(i&255) {
						int lsb = i & ((~i)+1);
						while(lsb>1){
							++val;
							lsb>>=1;
						}
					} else val = 8;
				} else {
					val = (cnt > 0 ? cnt + 8 : 0);
				}
				ans += dp[K][i][j][cnt] * val;
			}
		}
	}
	printf("%.12lf\n",ans);
	return 0;
}