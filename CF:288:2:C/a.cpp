#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int m,t,r;
int w, T[605], a[605];

int main(){
	scanf("%d%d%d",&m,&t,&r);
	int ans = 0;
	int prev = -1000;
	for(int i=0;i<m;++i){
		scanf("%d",&w);
		int k = r-T[w];
		if(k<=0)continue;
		ans += k;
		for(int j=k-1;j>=0;--j){
			if(w-j <= prev) {
				printf("-1\n");
				return 0;
			}
			a[max(0,w-j)]++;
			a[max(0,w+t-j)]--;
			prev = w-j;
		}
		for(int j=0;j<605;++j){
			if(j>0){
				a[j] = a[j] + a[j-1];
				a[j-1] = 0;
			}
			T[j] += a[j];
		}
		if(r-T[w] > 0) {
			printf("-1\n");
			return 0;
		}
	}
	printf("%d\n", ans);
	return 0;
}