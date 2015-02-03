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

/* MAYBE number of gcd s will be O(N^2) */
/* Accepted but maybe the test case is weak, or maybe number of gcd is really bounded at O(N^2) */
int N;
int u[303], v[303];
map<int,int> dp;
vector<int> st;
int gcd(int a, int b) {
	if(a < b) swap(a,b);
	if(b==0)return a;
	return gcd(b,a%b);
}

int main(){
	scanf("%d",&N);
	for(int i=0;i<N;++i){
		scanf("%d",&u[i]);
	}
	for(int i=0;i<N;++i){
		scanf("%d",&v[i]);
	}
	vector<int> tmp;
	for(int i=0;i<N;++i){
		for(int j=0;j<st.size();++j){
			int g = gcd(u[i],st[j]);
			if(dp.count(g)) {
				dp[g] = min(dp[g], v[i]+dp[st[j]]);
			} else {
				tmp.push_back(g);
				dp[g] = v[i] + dp[st[j]];
			}
		}
		if(dp.count(u[i])) {
			dp[u[i]] = min(dp[u[i]], v[i]);
		} else {
			tmp.push_back(u[i]);
			dp[u[i]] = v[i];
		}
		while(!tmp.empty()){
			st.push_back(tmp.back());
			tmp.pop_back();
		}
	}
	if(dp.count(1)){
		printf("%d\n", dp[1]);
	} else printf("-1\n");
	return 0;
}