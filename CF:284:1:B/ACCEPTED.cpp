#include <cstdio>
#include <cmath>

double p[5005];
int t[5005];
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
	double cur = 0;
	double tmp = 0;
	double q;
	for(int i=1;i<=N;++i){
		cur = 0;
		tmp = 0;
		q = pow(1-p[i-1],t[i-1]-1);
		for(int k=0;k<=T;++k){
			cur = cur * (1-p[i-1]) + prob[i-1][k];
			if(k >= t[i-1]-1){
				cur -= prob[i-1][k-t[i-1]+1] * q;
				prob[i][k] += prob[i-1][k-t[i-1]] * q;
			}
			if(k >= T-t[i-1] && k < T){
				tmp = prob[i-1][k+1] + (1-p[i-1]) * tmp;
			}
			prob[i][k+1] = cur * p[i-1];
		}
		ans += tmp * (i-1);
	}
	for(int k=0;k<=T;++k){
		ans += N * prob[N][k];
	}
	printf("%.12lf\n", ans);
	return 0;
}