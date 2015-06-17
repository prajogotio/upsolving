#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
int n;
int a[200010], b[200010];
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
	}
	for(int v=1;v<=n;++v){
		for(int k=1;2+k*(v-1)<=n && k<n;++k){
			for(int i=2+k*(v-1);i<=1+k*v && i<=n;++i){
				b[k] += (a[v] > a[i] ? 1 : 0);
			}
		}
	}
	for(int i=1;i<n;++i){
		printf("%d ",b[i]);
	}
	printf("\n");
	return 0;
}