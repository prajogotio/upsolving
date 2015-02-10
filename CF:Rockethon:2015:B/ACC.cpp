#include <cstdio>

int main(){
	int n;
	long long m;
	scanf("%d%I64d",&n,&m);
	long long bitmask = (1LL<<(n-1))- m;
	for(int i=n-2;i>=0;--i){
		if(bitmask&(1LL<<i))printf("%d ",n-i-1);
	}
	printf("%d",n);
	for(int i=0;i<n-1;++i){
		if(!(bitmask&(1LL<<i)))printf(" %d",n-i-1);
	}
	printf("\n");
	return 0;
}