#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

int n;
int a[1010], b[1010];
int main(){
	scanf("%d",&n);
	for(int j=0;j<2;++j){
		for(int i=0;i<n;++i){
			if(j==0)scanf("%1d",&a[i]);
			else scanf("%1d",&b[i]);
		}
	}
	int ans = 0;
	for(int i=0;i<n;++i){
		int x = min(a[i],b[i]);
		int y = max(a[i],b[i]);
		ans += min(y-x, x+10-y);
	}
	printf("%d\n",ans);
	return 0;
}