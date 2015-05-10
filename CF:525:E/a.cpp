#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;

int a[30];
int N, K;
long long S;
map<pair<long long,int> , int> m[2];
long long fact[20];
long long ans;

void comp(int mi, int ai, int n){
	for(int b=0, sz=(1<<n);b<sz;++b){
		int k = __builtin_popcount(b);
		for(int bb=0, ksz=(1<<k);bb<ksz;++bb){
			long long sum = 0;
			int ptr = 0;
			bool ok = true;
			for (int i=0;i<n;++i){
				if(!ok) break;
				if(!(b& (1<<i))) continue;
				int cur = i+ai;
				if(bb & (1<<ptr)) {
					if (a[cur] > 18) ok = false;
					else {
						sum += fact[a[cur]];
					}
				} else {
					sum += a[cur];
				}
				++ptr;
			}
			if(ok){
				if(mi == 0) {
					m[mi][make_pair(sum, __builtin_popcount(bb))]++;
				}else{
					long long sres = S - sum;
					for(int k=0;k<=K-__builtin_popcount(bb);++k){
						if(m[0].count(make_pair(sres,k))) {
							ans += m[0][make_pair(sres,k)];
						}
					}
				}
			}
		}
	}
}

int main(){
	fact[0] = 1;
	for(int i=1;i<=18;++i){
		fact[i] = fact[i-1] * i;
	}
	ans = 0;
	scanf("%d%d",&N,&K);
	cin >> S;
	for(int i=0;i<N;++i){
		scanf("%d",&a[i]);
	}
	comp(0, 0, N/2);
	comp(1, N/2, N - N/2);
	cout << ans;
	return 0;
}