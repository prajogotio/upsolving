#include <iostream>
#include <cstdio>
#include <algorithm>
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
double prob[5005][5005];
double sum[5005][5005];
double q[5005][5005];
int N, T;

int main(){
	scanf("%d%d", &N, &T);
	for(int i=0;i<N;++i){
		scanf("%lf%d", &p[i], &t[i]);
		p[i] *= 0.01;
	}
	prob[0][0] = 1;
	for(int i=1;i<=N+1;++i){
		//process sum and q first
		q[i-1][T] = 1;
		for(int k=T;k>=0;--k){
			if(k<T) q[i-1][k] = q[i-1][k+1] * (1-p[i-1]);
			if(p[i-1] == 1) {
				sum[i-1][k] = prob[i-1][k];
			} else {
				sum[i-1][k] = q[i-1][k] * prob[i-1][k];
			}
			if(k<T) sum[i-1][k] += sum[i-1][k+1];
		}
		if(i==N+1) break;
		//from i-1,k-j -> i,k for j < t[i-1]
		for(int k=1;k<=T;++k){
			prob[i][k] = sum[i-1][max(0,k-t[i-1]+1)] - sum[i-1][k];
			if(p[i-1] == 1) continue;
			prob[i][k] /= q[i-1][k] * (1-p[i-1]);
			prob[i][k] *= p[i-1];
		}
		//from i-1,k-t[i] -> i,k
		for(int k=t[i-1];k<=T;++k){
			printf("%d %d %d\n", i, k, t[i-1]);
			prob[i][k] += prob[i-1][k-t[i-1]] * q[i-1][T-t[i-1]+1];
		}
		for(int k=0;k<=T;++k){
			printf("%lf ", q[i-1][k]);
		}
		printf("\n");
	}
	
	printf("q:\n");
	for(int i=0;i<=N;++i){
		for(int j=0;j<=T;++j){
			printf("%4.3lf ", q[i][j]);
		}
		printf("\n");
	}
	printf("sum:\n");
	for(int i=0;i<=N;++i){
		for(int j=0;j<=T;++j){
			printf("%4.3lf ", sum[i][j]);
		}
		printf("\n");
	}
	printf("prob:\n");
	for(int i=0;i<=N;++i){
		for(int j=0;j<=T;++j){
			printf("%4.3lf ", prob[i][j]);
		}
		printf("\n");
	}
	//for all i,j -> i,T
	for(int i=1;i<N;++i){
		for(int j=T-t[i]+1;j<T;++j){
			prob[i][T] += prob[i][j] * q[i][j];
		}
	}
	for(int j=0;j<T;++j){
		prob[N][T] += prob[N][j];
	}
	double ans = 0;
	for(int i=1;i<=N;++i){
		ans += i * prob[i][T];
	}
	printf("%.12lf\n", ans);
	return 0;
}