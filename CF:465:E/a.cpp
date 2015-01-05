#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
long long MOD = (long long) 1e9 + 7LL;
int N;
int d[100005];
string t[100005];
long long val[11];
long long q[11];

int main(){
	cin >> t[0];
	d[0] = 0;
	scanf("%d", &N);
	for(int i=1;i<=N;++i){
		scanf("%d", &d[i]);
		cin >> t[i];
		t[i].erase(0, 2);
	}
	for(int i=0;i<10;++i){
		val[i] = i;
		q[i] = 10;
	}
	for(int i=N;i>=0;--i){
		int tlen = t[i].size();
		long long tval = 0;
		long long p10 = 1;
		for(int j=tlen-1;j>=0;--j){
			int g = t[i][j] - '0';
			tval += p10 * val[g];
			tval %= MOD;
			p10 *= q[g];
			p10 %= MOD;
		}
		val[d[i]] = tval;
		q[d[i]] = p10;
	}
	cout << val[0] << endl;
	return 0;
}