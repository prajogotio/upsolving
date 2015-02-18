#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

/*
Very cool idea, explained in official editorial.
W[m] number of vertices at distance m.
W[m] = sum [i=1..100] cnt[i] * W[m-i]
To find: S[x] = sum [i=0..x] W[x]
A:
W[1] W[2] .. W[100] S[100]

B:
0 0 0 0 cnt[100] cnt[100]
1 0 0 0 cnt[99]  cnt[99]
0 1 0 0 cnt[98]  cnt[98]
. . . . .        .
. . . . .        .
0 0 0 1 cnt[1]   cnt[1]
0 0 0 0 0        1
C = AB^(x-100)
answer = C[101]
*/
long long MOD = (long long) 1e9 + 7LL;
int cnt[103];
long long A[103], B[103][103], C[103][103];
int N, X;
long long temp[103][103];


void fast_multiplication(int k) {
	if(k==1){
		for(int i=0;i<=100;++i){
			for(int j=0;j<=100;++j){
				C[i][j] = B[i][j];
			}
		}
		return;
	}
	if(k%2){
		fast_multiplication(k-1);
		for(int i=0;i<=100;++i){
			for(int j=0;j<=100;++j){
				temp[i][j] = 0;
				for(int k=0;k<=100;++k){
					temp[i][j] += B[i][k] * C[k][j];
					temp[i][j] %= MOD;
				}
			}
		}
		for(int i=0;i<=100;++i){
			for(int j=0;j<=100;++j){
				C[i][j] = temp[i][j];
			}
		}
	} else {
		fast_multiplication(k/2);
		for(int i=0;i<=100;++i){
			for(int j=0;j<=100;++j){
				temp[i][j] = 0;
				for(int k=0;k<=100;++k){
					temp[i][j] += C[i][k] * C[k][j];
					temp[i][j] %= MOD;
				}
			}
		}
		for(int i=0;i<=100;++i){
			for(int j=0;j<=100;++j){
				C[i][j] = temp[i][j];
			}
		}
	}
}

int main(){
	int d;
	scanf("%d%d",&N,&X);
	for(int i=0;i<N;++i){
		scanf("%d",&d);
		cnt[d]++;
	}
	for(int i=0;i<99;++i){
		B[i+1][i] = 1;
	}
	for(int i=0;i<100;++i){
		B[i][99] = cnt[100-i];
		B[i][100] = cnt[100-i];
	}
	B[100][100] = 1;
	A[0] = 1;
	for(int i=1;i<=100;++i){
		A[i] = 0;
		for(int j=1;j<=i;++j){
			A[i] += 1LL * cnt[j] * A[i-j];
			A[i] %= MOD;
		}
	} 
	if(X <= 100){
		long long ans = 0;
		for(int i=0;i<=X;++i){
			ans += A[i];
			ans %= MOD;
		}
		cout << ans << endl;
	} else {
		for(int i=0;i<=100;++i){
			A[101] += A[i];
			A[101] %= MOD;
		}
		fast_multiplication(X-100);
		long long ans = 0;
		for(int i=0;i<=100;++i){
			ans += C[i][100] * A[i+1];
			ans %= MOD;
		}
		cout << ans << endl;
	}
	return 0;
}