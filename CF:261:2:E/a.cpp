#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
int INF = (int) 1e9;
vector<pair<int,pair<int,int> > > st;
int dp[300005];
int N, M;
int main(){
	int u,v,w;
	scanf("%d%d", &N, &M);
	for(int i=0;i<M;++i){
		scanf("%d %d %d", &u,&v,&w);
		st.push_back(make_pair(w,make_pair(u,v)));
	}
	sort(st.begin(),st.end());
	int ans = 0;
	vector<pair<int,int> > p;
	for(int i=M-1;i>=0;--i){
		w = st[i].first;
		u = st[i].second.first;
		v = st[i].second.second;
		//printf("%d->%d %d\n",u,v,w);
		int tmp = max(1, max(dp[u], 1+dp[v]));
		p.push_back(make_pair(u,tmp));
		if(i==0 || w != st[i-1].first){
			while(!p.empty()){
				pair<int,int> cur = p.back();
				p.pop_back();
				dp[cur.first] = max(dp[cur.first],cur.second);
				ans = max(ans, dp[cur.first]);
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}