#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int a[50000];
int vis[50000];
int N, T;
bool ok;

void dfs(int u){
	if(ok) return;
	if(u == T) {
		ok = true;
		return;
	}
	vis[u] = 1;
	if(vis[a[u]+u])return;
	dfs(a[u]+u);
}

int main(){
	scanf("%d%d", &N, &T);
	for(int i=1;i<=N;++i){
		scanf("%d", &a[i]);
	}
	ok = false;
	dfs(1);
	if(ok) printf("YES\n");
	else printf("NO\n");
	return 0;
}