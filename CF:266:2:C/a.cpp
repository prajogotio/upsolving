#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

long long sum[500003];
int N;
int main(){
	scanf("%d",&N);
	for(int i=1;i<=N;++i){
		scanf("%I64d",&sum[i]);
		sum[i] += sum[i-1];
	}
	if(sum[N]%3LL!=0)printf("0\n");
	else {
		long long u = sum[N]/3LL;
		long long v = 2LL * u;
		long long cnt = 0, ans = 0;
		for(int i=N-1;i>=1;--i){
			if(sum[i] == u)	ans += cnt;
			if(sum[i] == v) ++cnt;
		}
		cout << ans << endl;
	}
	return 0;
}