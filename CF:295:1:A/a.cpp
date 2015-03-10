#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int N;
	string s;
	scanf("%d",&N);
	cin >> s;
	int c,a,g,t;
	c=a=g=t=0;
	for(int i=0;i<N;++i){
		if(s[i]=='C')++c;
		if(s[i]=='G')++g;
		if(s[i]=='A')++a;
		if(s[i]=='T')++t;
	}
	int n = max(c,max(g,max(a,t)));
	int cnt = 0;
	if(c==n)cnt++;
	if(g==n)cnt++;
	if(t==n)cnt++;
	if(a==n)cnt++;
	long long ans = 1;
	long long MOD = (long long) 1e9 + 7LL;
	for(int i=0;i<N;++i){
		ans *= cnt;
		ans %= MOD;
	}
	cout << ans << endl;
}