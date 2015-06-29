#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

namespace cf {
int n, m;
string s[22];
int a[22][22];
int dp[1<<21];
int vis[1<<21];
vector<vector<int> > bm, b;
int inf = (int) 1e8;
int dfs(int mask) {
	if(vis[mask]) return dp[mask];
	vis[mask] = 1;
	int next = -1;
	for(int i=0;i<n;++i){
		if(!(mask&(1<<i))){
			next = i;
			break;
		}
	}
	int cur = inf;
	for(int j=0;j<m;++j){
		cur = min(cur, dfs(mask|(1<<next)) + a[next][j]);
	}
	for(int j=0;j<m;++j){
		for(int k=0;k<bm[j].size();++k){
			if ( (bm[j][k] | mask) == mask ) continue;
			cur = min(cur, dfs(mask|bm[j][k]) + b[j][k]);
		}
	}
	dp[mask] = cur;


	// printf("%d ", mask);
	// for(int i=0;i<n;++i){
	// 	if(mask & (1<<i)) printf("1"); else printf("0");
	// }
	// printf(" lowest: %d\n",cur);

	return cur;
}

void solve() {
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i){
		cin >> s[i];
	}
	for(int i=0;i<n;++i){
		for(int j=0;j<m;++j){
			scanf("%d",&a[i][j]);
		}
	}
	bm = vector<vector<int> > (22);
	b = vector<vector<int> > (22);
	for(int i=0;i<m;++i){
		int v[22];
		for(int j=0;j<n;++j) v[j] = 0;
		for(int j=0;j<n;++j){
			if(v[j]) continue;
			int mask = 0;
			int sum = 0;
			int hi = 0;
			for(int k=j;k<n;++k){
				if(s[k][i] != s[j][i]) continue;
				mask ^= (1<<k);
				v[k] = 1;
				sum += a[k][i];
				hi = max(hi, a[k][i]);
			}

			// printf("for column %d ", i);
			// for(int i=0;i<n;++i){
			// 	if(mask & (1<<i)) printf("1"); else printf("0");
			// }
			// printf(" lowest: %d\n",sum-hi);

			bm[i].push_back(mask);
			b[i].push_back(sum-hi);
		}
	}
	vis[(1<<n)-1] = 1;
	dfs(0);
	printf("%d\n", dp[0]);	
}


}

int main(){ 
	cf::solve();
	return 0;
}