#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
#include <queue>
#include <cmath>
#include <cassert>
#include <map>
#include <set>
using namespace std;
int INF = (int) 1e9;
int mark[100000];
int N;
int dp[600];
int val[303], cost[303];
vector<int> primes;
vector<int> factors[303];
int main(){
	for(int i=2;i*i<=100000;++i){
		for(int j=2;i*j<=100000;++j){
			mark[i*j] = 1;
		}
	}
	for(int i=2;i<=100000;++i){
		if(mark[i]==0)primes.push_back(i);
	}
	scanf("%d",&N);
	for(int i=0;i<N;++i){
		scanf("%d",&val[i]);
		bool isprime = true;
		for(int k=0;k<primes.size();++k){
			if(val[i]%primes[k])continue;
			isprime = false;
			factors[i].push_back(primes[k]);
		}
		if(isprime && val[i] != 1) factors[i].push_back(val[i]);
	}
	for(int i=0;i<N;++i){
		scanf("%d",&cost[i]);
	}
	int ans = INF;
	for(int k=0;k<N;++k){
		for(int i=0;i<600;++i)dp[i]=INF;
		dp[(1<<((int)factors[k].size()))-1] = cost[k];
		for(int i=0;i<N;++i){
			if(i == k) continue;
			int bm = 0;
			for(int j=0;j<factors[k].size();++j){
				for(int jj=0;jj<factors[i].size();++jj){
					if(factors[k][j]==factors[i][jj]){
						bm |= (1<<j);
						break;
					}
				}
			}
			for(int j=0;j<(1<<9);++j){
				int g = bm & j;
				dp[g] = min(dp[g], dp[j] + cost[i]);
			}
		}
		ans = min(ans, dp[0]);
	}
	if(ans != INF) {
		printf("%d\n",ans);
	}else{
		printf("-1\n");
	}
	return 0;
}