#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

int a[5003];
int K, N;


bool found(int val){
	int lo=0,hi=N,mid;
	while(lo<=hi){
		mid = (lo+hi)/2;
		if(a[mid] == val) return true;
		if(a[mid] < val){
			lo = mid+1;
		} else {
			hi = mid-1;
		}
	}
	return false;
}

void solve(int val){
	int ret = 12345678;
	for(int i=0;i<=K;++i){
		for(int j=0;j<=K-i;++j){
			for(int k=0;k<N;++k){
				if(a[k]*i > val) break;
				int res = val - a[k]*i;
				if(res == 0) {
					ret = min(ret,i);
					continue;
				}
				if(j == 0) continue;
				if(res%j) continue;
				res /= j;
				if(found(res)){
					ret = min(ret,i+j);
					continue;
				}
			}
		}
	}
	if(ret > K) ret = -1;
	printf("%d\n",ret);
	return;
}

int main(){
	scanf("%d%d",&N,&K);
	for(int i=0;i<N;++i){
		scanf("%d",&a[i]);
	}
	int q;
	scanf("%d",&q);
	for(int qq=0;qq<q;++qq){
		int val;
		scanf("%d",&val);
		solve(val);
	}
	return 0;
}