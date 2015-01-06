#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int c[1003][1003];

int main(){
	int n,k,d;
	scanf("%d%d%d", &n,&k,&d);
	if(k>=n){
		for(int i=0;i<d;++i){
			for(int j=1;j<=n;++j){
				if(j!=1)printf(" ");
				printf("%d", j);
			}
			printf("\n");
		}
	} else {
		int check = 1;
		bool ok = false;
		for(int i=0;i<d;++i){
			check *= k;
			if(check >= n){
				ok = true;
				break;
			}
		}
		if(ok){
			int a[1003];
			for(int i=0;i<d;++i)a[i]=1;
			for(int j=0;j<n;++j){
				for(int i=0;i<d;++i){
					c[i][j] = a[i];
				}
				a[0] += 1;
				int t = 0;
				while(a[t] > k){
					a[t+1] += 1;
					a[t] = 1;
					++t;
				}
			}
			for(int i=0;i<d;++i){
				for(int j=0;j<n;++j){
					if(j!=0)printf(" ");
					printf("%d",c[i][j]);
				}
				printf("\n");
			}
		} else {
			printf("-1\n");
		}
	}
	return 0;
}