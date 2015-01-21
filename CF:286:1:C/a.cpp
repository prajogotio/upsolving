#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
long long a[100005],h[100005];
int N, M, K;
long long P;
int day[5003];
int t[100005];
bool check(long long X) {
	for(int i=0;i<M;++i){day[i] = 0;}
	long long sum = 0;
	for(int i=0;i<N;++i){
		long long T = max(0LL, (h[i]+a[i]*M-X)/P + ((h[i]+a[i]*M-X) % P == 0 ? 0 : 1LL));
		if((h[i]+a[i]*M-X)<0) T = 0;
		t[i] = (int) T;
		sum += T;
	}
	if(sum > K*M) return false;

	for(int i=0;i<N;++i){
		long long H = h[i];
		long long Dr = M;
		long long Tr = t[i];
		long long d = 0;
		while(Tr > 0) {
			long long bigger = (P-H)/a[i] + ((P-H)%a[i] == 0 ? 0 : 1LL);
			if((P-H)<0)bigger = 0;
			long long smaller = (Dr*a[i] - (Tr-1)*P - X)/a[i] + ((Dr*a[i] - (Tr-1)*P - X)%a[i] == 0 ? 0 : 1LL);
			if((Dr*a[i] - (Tr-1)*P - X) < 0)smaller = 0;
			if(smaller < bigger){
				day[d+(int)smaller]++;
				Dr -= smaller;
				H = 0;
				d += smaller;
				if(d >= M) return false;
			} else {
				day[d+(int)bigger]++;
				Dr -= bigger;
				d += bigger;
				if(d >= M) return false;
				H = H + bigger * a[i] - P;
			}
			--Tr;
		}
	}

	for(int i=0;i<M-1;++i){
		if(day[i] > K){
			day[i+1] += day[i]-K;
			//day[i] = K;
		}
	}
	return (day[M-1]<=K);
}

int main(){
	int u,v;
	scanf("%d%d%d",&N,&M,&K);
	cin >> P;
	for(int i=0;i<N;++i){
		scanf("%d%d",&u,&v);
		h[i] = u;
		a[i] = v;
	}
	long long lo = 0, hi = (long long) 5e13, mid;
	while(lo <= hi){
		mid = (lo+hi)/2LL;
		if(check(mid)){
			hi = mid-1LL;
		} else {
			lo = mid+1LL;
		}
	}
	cout << lo << endl;
	return 0;
}