#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int s[200005], p[200005];
int par[200005];

int main(){
	int n, m, u;
	scanf("%d%d", &n,&m);
	for(int i=0;i<n;++i){
		if(i==0) scanf("%d", &s[i]);
		else {
			scanf("%d", &u);
			s[i-1] = u - s[i-1];
			s[i] = u;
		}
	}
	for(int j=0;j<m;++j){
		if(j==0) scanf("%d", &p[j]);
		else {
			scanf("%d", &u);
			p[j-1] = u - p[j-1];
			p[j] = u;
		}
	}
	n--; m--;
	//special case: m == 0
	if(m == 0) {
		printf("%d\n", n+1);
		return 0;
	}
	//otherwise:
	par[0] = -1;
	int k = -1;
	for(int i=1;i<m;++i){
		while(k != -1 && p[k+1] != p[i]) {
			k = par[k];
		}
		if(p[k+1] == p[i]) {
			++k;
		}
		par[i] = k;
	}
	k = -1;
	int cnt = 0;
	for(int i=0;i<n;++i){
		while(k != -1 && p[k+1] != s[i]){
			k = par[k];
		}
		if(p[k+1] == s[i]){
			++k;
		}
		if(k == m-1) ++cnt;
	}
	printf("%d\n", cnt);
	return 0;
}