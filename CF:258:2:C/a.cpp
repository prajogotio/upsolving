#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cassert>
using namespace std;

int main(){
	int tc;
	scanf("%d",&tc);
	long long n,k,d1,d2;
	long long a[2]={1,-1};
	while(tc--){
		cin >> n >> k >> d1 >> d2;
		if(n%3LL!=0){
			printf("no\n");
			continue;
		}
		long long t = n/3LL;
		bool found = false;
		for(int i=0;i<2;++i){
			for(int j=0;j<2;++j){
				long long t3 = k - 2*a[j]*d2 - a[i]*d1;
				if(t3%3LL!=0)continue;
				t3/=3LL;
				if(t3<0)continue;
				long long t2 = a[j]*d2+t3;
				if(t2<0)continue;
				long long t1 = a[i]*d1+t2;
				if(t1<0)continue;
				if(t1<=t&&t2<=t&&t3<=t)found = true;
			}
			if(found) break;
		}
		if(found)printf("yes\n"); else printf("no\n");
	}
	return 0;
}