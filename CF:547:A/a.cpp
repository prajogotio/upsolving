#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
long long m;
int h[2],a[2],x[2],y[2];
const int inf = 12345678;
int cmp(int s, int t, int x, int y) {
	long long cur = s;
	for(int i=1;i<=m;++i){
		cur = (cur*x+y)%m;
		if(cur == t) return i;
	}
	return inf;
}

int main(){
	cin >> m;
	for(int i=0;i<2;++i)scanf("%d%d%d%d",&h[i],&a[i],&x[i],&y[i]);
	int r[2];
	for(int i=0;i<2;++i){
		r[i] = (h[i]==a[i]?0:cmp(h[i],a[i],x[i],y[i]));
		if(r[i]==inf) {
			printf("-1\n");
			return 0;
		}
	}
	int p[2];
	for(int i=0;i<2;++i){
		p[i] = cmp(a[i],a[i],x[i],y[i]);
	}
	if(p[0] == inf || p[1] == inf) {
		if(p[0]==inf && p[1]==inf) {
			if(r[0] == r[1]) cout << r[0] << endl;
			else printf("-1\n");
		} else {
			int q = (p[0]==inf?p[1]:p[0]);
			int res = (p[0]==inf?r[0]-r[1]:r[1]-r[0]);
			int s = (p[0]==inf?r[0]:r[1]);
			int val = res/q;
			if(val>=0 && val*q==res){
				cout<<s<<endl;
			}else printf("-1\n");
		}
		return 0;
	}
	for(int i=0;i<m;++i){
		long long val = 1LL*r[0]-r[1]+1LL*i*p[0];
		if(val >= 0 && val%p[1]==0) {
			cout << (1LL*r[0]+1LL*i*p[0]) << endl;
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}