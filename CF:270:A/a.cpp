#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int N = 1000000;
int num[1000003];

int main(){
	for(int i=2;i<=N;++i){
		for(int j=2;j<=N/i;++j){
			num[i*j] = 1;
		}
	}
	int n;
	scanf("%d", &n);
	for(int i=3;i<=n-2;++i){
		if(num[i] && num[n-i]){
			printf("%d %d\n", i, n-i);
			return 0;
		}
	}
	return 0;
}