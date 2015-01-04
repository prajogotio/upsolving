#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

/*
W[i][k] = number of ways to have k open segments
by the time we reach i.
*/

long long MOD = (long long) 1e9 + 7LL;
int N, H;
long long W[2003][2003];
int a[2003];


int main(){
	scanf("%d%d", &N,&H);
	for(int i=1;i<=N;++i){
		scanf("%d",&a[i]);
	}
	W[0][0] = 1;
	for(int i=1;i<=N;++i){
		long long diff = H - a[i];
		if(diff < 0 || diff > (long long) (N-i+1)){
			printf("0\n");
			return 0;
		}
		int k = diff;
		//dont do anything
		W[i][k] = W[i-1][k];
		//close and open
		if(k>0)W[i][k] += W[i-1][k]*k;
		W[i][k] %= MOD;
		//add 1
		if(k>0)W[i][k] += W[i-1][k-1];
		W[i][k] %= MOD;
		//close 1
		W[i][k] += W[i-1][k+1]*(k+1);
		W[i][k] %= MOD;

		if(i == N) cout << W[i][k] << endl;
	}

	return 0;
}