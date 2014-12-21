#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int a[3000];
int main(){
	int n, k;
	scanf("%d%d", &n,&k);
	for(int i=0;i<n;++i){
		scanf("%d", &a[i]);
	}
	sort(a, a+n);
	int ans = 0;
	for(int i=n-1;i>=0;i-=k){
		int tmp = a[i] - 1;
		ans += 2*tmp;
	}
	printf("%d\n", ans);
	return 0;
}