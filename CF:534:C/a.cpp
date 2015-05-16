#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

long long s[200010];
int d[200010];
int n;
long long a;
int main(){
	scanf("%d",&n);
	cin >> a;
	for(int i=0;i<n;++i){
		scanf("%d",&d[i]);
		s[i] = (long long)d[i] + (i>0 ? s[i-1] : 0);
	}
	for(int i=0;i<n;++i){
		long long left = (i>0 ? s[i-1] : 0);
		long long right = s[n-1]-s[i];
		long long lo = a - left - right,
				  hi = a - (n-1);
		if(d[i] < lo || hi < 1) {
			printf("%d ", d[i]);
		} else if (lo <= 1 && d[i] <= hi){
			printf("0 ");
		} else {
			printf("%d ", (int)(max(d[i]-hi,0LL) + max(lo-1LL,0LL)));
		}
	}
	printf("\n");
	return 0;
}