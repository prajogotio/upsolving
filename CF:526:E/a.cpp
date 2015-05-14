#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int len[1000005];
int a[1000005];
int n, q;
long long b;


void solve(){
	long long sum=a[0];
	int i=0,j=1;
	int midx=0;
	for(int i=0;i<n;++i){
		if(i!=0) sum -= a[i-1];
		if(j==i) {
			sum += a[j++];
			j %= n;
		}
		while(j!=i && sum+a[j]<=b){
			sum+=a[j];
			j = (j+1) % n;
		}
		len[i] = j-i + (j-i <= 0 ? n : 0);
		if(len[midx] > len[i]) midx=i;
	}
	int minans = (int)1e8;
	for(int k=midx;k<=midx+len[midx];++k){
		int i = k%n;
		int ans = 0;
		int tot = 0;
		while(tot < n){
			ans++;
			tot += len[i];
			i = (i+len[i])%n;
		}
		minans = min(minans, ans);
	}
	printf("%d\n",minans);
}

int main(){
	scanf("%d%d",&n,&q);
	for(int i=0;i<n;++i){
		scanf("%d",&a[i]);
	}
	for(int qq=0;qq<q;++qq){
		cin>>b;
		solve();
	}
	return 0;
}