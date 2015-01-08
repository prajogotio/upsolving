#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

double fast_exponentiation(double x, int n){
	if(n==0)return 1.0;
	if(n%2==0){
		double ret = fast_exponentiation(x,n/2);
		return ret * ret;
	} else {
		return x * fast_exponentiation(x,n-1);
	}
}

int main(){
	int n,m;
	scanf("%d%d",&m,&n);
	double tmp = fast_exponentiation(1.0/(double)m,n);
	double ans = tmp;
	for(int i=2;i<=m;++i){
		double cum = fast_exponentiation((double)i/(double)m,n);
		ans += (cum-tmp)*i;
		tmp = cum;
	}
	printf("%.12lf\n",ans);
	return 0;
}