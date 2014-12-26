#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

/* TLE */

/*
prob[i,k] = probability of answering i questions in exactly at k seconds.
prob[0,0] = 1;
prob[i,k] = prob[i-1][k-j] * p[i-1] * (1-p[i-1]) ^ (j-1)
for all j = 1,...,t[i-1], and where p[i-1] = 1 when j = t[i-1].

E(x) = i * prob[i]
*/

double p[5005];
int t[5005];
double q[5005];
double prob[5005][5005];
int N, T;

int main(){
	scanf("%d%d", &N, &T);
	for(int i=0;i<N;++i){
		scanf("%lf%d", &p[i], &t[i]);
		p[i] *= 0.01;
	}
	prob[0][0] = 1;
	double ans = 0;
	for(int i=1;i<=N;++i){
		double cur = 0;
		q[0] = 1;
		for(int k=1;k<=T;++k){
			q[k] = q[k-1];
			if(k <= t[i-1]) q[k] *= (1-p[i-1]);
		}
		for(int k=0;k<T;++k){
			cur = cur * (1-p[i-1]) + prob[i-1][k];
			if(k >= t[i-1]-1){
				cur -= prob[i-1][k-t[i-1]+1]*q[t[i-1]-1];
			}
			prob[i][k+1] = cur * p[i-1];
		}
		for(int k=t[i-1];k<=T;++k){
			prob[i][k] += prob[i-1][k-t[i-1]] * q[t[i-1]-1];
		}
		for(int k=T-t[i-1]+1;k<=T;++k){
			ans += (i-1) * prob[i-1][k] * q[T-k];
		}
	}
	for(int k=0;k<=T;++k){
		ans += N * prob[N][k];
	}
	printf("%.12lf\n", ans);
	return 0;
}