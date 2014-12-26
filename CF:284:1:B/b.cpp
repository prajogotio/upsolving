#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

/* MEMORY LIMIT EXCEEDED*/


/*
prob[i,k] = probability of answering i questions in exactly at k seconds.
prob[0,0] = 1;
prob[i,k] = prob[i-1][k-j] * p[i-1] * (1-p[i-1]) ^ (j-1)
for all j = 1,...,t[i-1], and where p[i-1] = 1 when j = t[i-1].

E(x) = i * prob[i]
*/

double p[5005];
int t[5005];
double prob[2][5005];
double sum[2][5005];
double q[2][5005];
int N, T;

int main(){
	scanf("%d%d", &N, &T);
	for(int i=0;i<N;++i){
		scanf("%lf%d", &p[i], &t[i]);
		p[i] *= 0.01;
	}
	double ans = 0;
	prob[0][0] = 1;
	for(int i=1;i<=N+1;++i){
		int prev = (i&1)^1;
		//process sum and q first
		q[prev][T] = 1;
		for(int k=T;k>=0;--k){
			if(k<T) q[prev][k] = q[prev][k+1] * (1-p[i-1]);
			if(p[i-1] == 1) {
				sum[prev][k] = prob[prev][k];
			} else {
				sum[prev][k] = q[prev][k] * prob[prev][k];
			}
			if(k<T) sum[prev][k] += sum[prev][k+1];
		}
		if(i==N+1) break;
		//from i,j -> i,T
		for(int j=T-t[i-1]+1;j<T;++j){
			prob[prev][T] += prob[prev][j] * q[prev][j];
		}
		ans += (i-1) * prob[prev][T];
		memset(prob[i&1], 0, sizeof prob[i&1]);
		//from i-1,k-j -> i,k for j < t[i-1]
		for(int k=1;k<=T;++k){
			prob[i&1][k] = sum[prev][max(0,k-t[i-1]+1)] - sum[prev][k];
			if(p[i-1] == 1) continue;
			prob[i&1][k] /= q[prev][k] * (1-p[i-1]);
			prob[i&1][k] *= p[i-1];
		}
		//from i-1,k-t[i] -> i,k
		for(int k=t[i-1];k<=T;++k){
			prob[i&1][k] += prob[prev][k-t[i-1]] * q[prev][T-t[i-1]+1];
		}
	}

	for(int j=0;j<=T;++j){
		ans += N * prob[N&1][j];
	}
	
	printf("%.12lf\n", ans);
	return 0;
}