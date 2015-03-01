#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int main(){
	int N, M;
	scanf("%d%d",&N,&M);
	int lo = 0, hi = (N+M), mid;
	while(lo <= hi){
		mid = (lo+hi)/2;
		int lower = max(0, 2*mid - N);
		int upper = min(mid, M-mid);
		if(lower <= upper) {
			lo = mid+1;
		} else {
			hi = mid-1;
		}
	}
	printf("%d\n",hi);
	return 0;
}