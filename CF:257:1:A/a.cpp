#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

long long N,M,K;

int main(){
	cin >> N >> M >> K;
	if(N+M<K+2){
		printf("-1\n");
		return 0;
	}
	long long ans = -1;
	if(K-N+2LL <= M){
		ans = max(ans, (N/min(K+1LL,N)) * (M/max(1LL,K-N+2LL)));
	}
	if(K-M+2LL <= N){
		ans = max(ans, (M/min(K+1LL,M))*(N/max(1LL,K-M+2LL)));
	}
	cout << ans << endl;
	return 0;
}