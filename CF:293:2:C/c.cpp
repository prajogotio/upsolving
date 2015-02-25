#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#include <set>
#include <string>
using namespace std;

int N, M, K;
int p[100005], a[100005];

int main(){
	scanf("%d%d%d",&N,&M,&K);
	int u;
	long long ans = 0;
	for(int i=1;i<=N;++i){
		scanf("%d",&p[i]);
		a[p[i]] = i;
	}
	for(int i=1;i<=M;++i){
		scanf("%d",&u);
		int screen = (a[u]-1)/K;
		ans += screen+1;
		int pos = a[u];
		if(pos == 1) continue;
		int v = p[pos-1];
		a[u] = a[v];
		a[v] = pos;
		p[pos-1] = u;
		p[pos] = v;
	}
	cout << ans << endl;
	
	return 0;
}