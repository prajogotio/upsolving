#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;

int n, m, t;
string s;
int p[1000005], q[1000005];
int mark[1000005];
long long MOD = (long long) 1e9 + 7;

bool check(int prev, int y){
	int len = t - y + prev;
	return q[len];
}

int main(){
	scanf("%d%d",&n,&m);
	cin >> s;
	p[0] = 0, p[1] = 0;
	t = s.size();
	for(int i=2;i<=t;++i){
		int j = p[i-1];
		if(j != 0 && s[j] != s[i-1]) j = p[j];
		if(s[j] == s[i-1])++j;
		p[i] = j;
	}
	int j = t;
	while(j>0){
		q[j] = 1;
		j = p[j];
	}
	int y, prev = -1;
	for(int k=0;k<m;++k){
		scanf("%d",&y);
		if(mark[y] == 0){
			prev = y;
			for(int i=y;i<y+t;++i)mark[i]=1;
		} else {
			if(check(prev, y)){
				for(int i=prev+t;i<y+t;++i)mark[i]=1;
				prev = y;
			} else {
				printf("0\n");
				return 0;
			}
		}
	}
	long long ans = 1;
	for(int k=1;k<=n;++k){
		if(!mark[k]){
			ans *= 26;
			ans %= MOD;
		}
	}
	cout << ans << endl;
	return 0;
}