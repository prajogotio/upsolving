#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int a[100005];
int N;
int main() {
	scanf("%d",&N);
	for(int i=0;i<N;++i){
		scanf("%d",&a[i]);
	}
	sort(a, a+N);
	long long ans = 0;
	long long prev = 0;
	for(int i=N-1;i>=0;){
		if(a[i] == a[i-1] || a[i] == a[i-1]+1){
			if(prev != 0LL){
				ans += prev * ((a[i]+a[i-1])/2LL);
				prev = 0;
			} else {
				prev = (a[i]+a[i-1])/2LL;
			}
			i -= 2;
		} else {
			i--;
		}
	}
	printf("%I64d\n", ans);
	return 0;
}