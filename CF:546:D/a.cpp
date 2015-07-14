#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

int p[5000010];
int val[5000010];
long long fact[5000010];
int main(){
	for (int i = 0; i<=5000000;++i) val[i] = i;
	for (int i = 2; i<=5000000;++i) {
		if(p[i] != 0) continue;
		p[i] = 1;
		for (int j = 2; i*j<=5000000;++j) {
			int cur = j*i;
			while(val[cur]%i == 0) {
				val[cur]/=i;
				p[cur]++;
			}
		}
	}
	fact[1] = 0;
	for (int i = 2; i <= 5000000;++i) {
		fact[i] = fact[i-1] + p[i];
	}
	int t;
	scanf("%d",&t);
	for (int T=0;T<t;++T){
		int a,b;
		scanf("%d %d", &a, &b);
		printf("%I64d\n", fact[a]-fact[b]);
		//cout << (fact[a] - fact[b]) << endl;
	}
	return 0;
}