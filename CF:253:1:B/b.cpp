#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
double p[103];
double EPS = 1e-30;
int N;
int main(){
	scanf("%d",&N);
	for(int i=0;i<N;++i){
		scanf("%lf",&p[i]);
	}
	sort(p,p+N);
	double ans = 0;
	double sum = 0;
	double prob = 1;
	if(fabs(p[N-1]-1.0)<EPS) {printf("%.12lf\n",p[N-1]);return 0;}
	for(int i=N-1;i>=0;--i){
		sum += p[i] / (1.0 - p[i]);
		prob *= (1-p[i]);
		ans = max(ans,sum*prob);
		if(sum > 1.0) break;
	}
	printf("%.12lf\n",ans);
	return 0;
}