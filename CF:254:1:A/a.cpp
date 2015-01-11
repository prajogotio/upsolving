#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

int val[503];
int N,M;
int main(){
	int u,v,w;
	scanf("%d%d",&N,&M);
	for(int i=1;i<=N;++i){
		scanf("%d",&val[i]);
	}
	double ans = 0;
	for(int i=0;i<M;++i){
		scanf("%d%d%d",&u,&v,&w);
		double tmp = 1.0 * (val[u] + val[v]) / w;
		if(tmp > ans) ans = tmp;
	}
	printf("%.12lf\n", ans);
	return 0;
}