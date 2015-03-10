#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;

long long MOD = (long long) 1e9 + 7LL;

void gcd(long long a, long long b, long long &m, long long &x, long long &y) {
	if(a > b) {
		gcd(b, a, m, y, x);
		return;
	}
	if(a == 0) {
		m = b;
		x = 0;
		y = 1;
		return;
	}
	long long _x, _y;
	gcd(b%a, a, m, _y, _x);
	y = _y;
	x = _x - (b/a) * y;
	x %= MOD;
	y %= MOD;
}

long long inv[100005];
long long fact[100005], inv_fact[100005];
long long S[100005], sum[100005];
int N, K;
int main(){
	scanf("%d%d",&N,&K);
	for(int i=1;i<=N;++i){
		long long m,x,y;
		gcd(i,MOD,m,x,y);
		inv[i] = x;
	}
	fact[N-K-1] = 1LL;
	for(int i=N-K;i<=N-1;++i){
		fact[i] = fact[i-1] * i;
		fact[i] %= MOD;
	}
	inv_fact[0] = 1LL;
	for(int i=1;i<=N;++i){
		inv_fact[i] = inv_fact[i-1] * inv[i];
		inv_fact[i] %= MOD;
	}
	string d;
	cin >> d;
	if( K == 0 ) {
		long long ans = 0;
		for(int i=0;i<N;++i){
			ans *= 10LL;
			ans += d[i] - '0';
			ans %= MOD;
		}
		cout << ans << endl;
		return 0;
	}
	for(int i=0;i<N;++i){
		sum[i] = d[i] - '0';
		if(i > 0) sum[i] += sum[i-1];
		sum[i] %= MOD;
	}
	long long last_term = 0;
	long long pow10 = 1LL;
	for(int i=1;i<=N;++i){
		if(i == 1) {
			S[i] = sum[N-1];
		} else {
			S[i] = ((S[i-1] - last_term) * 10LL)%MOD + sum[N-1] - sum[i-2];
			S[i] %= MOD;
		}
		last_term += (d[N-i] - '0') * pow10;
		last_term %= MOD;
		pow10 *= 10LL;
		pow10 %= MOD;

	}
	long long mult, nmult = (K == 1 ? 1 : fact[N-2] * inv_fact[K-1]);
	long long ans = 0;
	if(K >= 2) mult = ( K == 2 ? 1 : fact[N-3] * inv_fact[K-2]);
	else mult = 0;
	mult %= MOD;
	nmult %= MOD;
	long long suffix = 0, prefix = 0;
	pow10 = 1LL;
	for(int i=1;i<=N-K;++i){
		suffix += (d[N-i] - '0') * pow10;
		prefix *= 10LL;
		prefix += d[i-1] - '0';
		prefix %= MOD;
		suffix %= MOD;
		pow10 *= 10LL;
		pow10 %= MOD;
		ans += ((S[i] - suffix - prefix) * mult)%MOD + ((suffix + prefix) * nmult)%MOD;
		ans %= MOD;

		if(K!=2) mult *= (inv[N-i-2] * (N-i-2-K+2))%MOD;
		if(K!=1) nmult *= (inv[N-i-1] * (N-i-1-K+1))%MOD;
		mult %= MOD; nmult %= MOD;
		if(nmult < 0) nmult += MOD;
	}
	if(ans<0)ans += MOD;
	cout << ans << endl;
	return 0;
}