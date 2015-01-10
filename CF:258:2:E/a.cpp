#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int n;
long long s;
long long f[23];
long long MOD = (long long)1e9 + 7LL;
long long d[23];
/* extended euclid
ax+by = 1 = bx'+qy'
q = a%b = a - (a/b)*b
bx' + (a-(a/b)*b)y' = b(x'-(a/b)y') + a(y')
y <- x'-(a/b)y'
x <- y'
*/

void euclid(long long a, long long b, long long *p){
	if(a < b)swap(a,b);
	if(b==0){
		p[0] = 1;
		p[1] = 0;
		return;
	}
	euclid(b, a%b, p);
	long long x = p[0] - (a/b)*p[1];
	long long y = p[1];
	p[1] = x; p[0] = y;
}

int main(){
	for(int i=1;i<=20;++i){
		long long p[2];
		euclid(MOD,i, p);
		d[i] = p[1];
	}
	scanf("%d",&n);
	cin >> s;
	for(int i=0;i<n;++i){
		cin >> f[i];
	}
	int sz = 1<<n;
	long long ans = 0;
	for(int i=0;i<sz;++i){
		int cnt = 0;
		int tmp = i;
		long long sum = 0;
		for(int k=0;k<n;++k){
			if(tmp&1){
				++cnt;
				sum += f[k]+1LL;
			}
			tmp >>= 1;
		}
		if(sum > s)continue;
		long long ret = s - sum + n - 1;
		ret %= MOD;
		long long cur = 1;
		for(int k=1;k<n;++k){
			cur *= ret;
			cur %= MOD;
			cur *= d[k];
			cur %= MOD;
			--ret;
		}
		if(cnt%2==0)ans += cur;
		else ans -= cur;
		ans %= MOD;
	}
	if(ans < 0) ans += MOD;
	printf("%d\n", (int) ans);
	return 0;
}