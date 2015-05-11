#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

int n;
int s[3003];
int m[3003];
priority_queue<pair<int,int> > pq;

void upd(int p, int val){
	vector<int> st;
	st.push_back(p);
	while(!st.empty()){
		int cur = st.back();
		st.pop_back();
		s[cur] += val;
		if(cur*2 < (1<<(n+1))){
			st.push_back(2*cur);
			st.push_back(2*cur+1);
		}
		if(cur>=(1<<n) && !m[cur]){
			pq.push(make_pair(s[cur],cur));
		}
	}
}

int main(){
	scanf("%d",&n);
	s[1] = 0;
	int w;
	int sz=(1<<(n+1));
	int mx=-1;
	for(int i=2;i<sz;++i){
		scanf("%d",&w);
		s[i] += s[i/2] + w;
		mx = max(mx, s[i]);
		if(i>=(1<<n)){
			pq.push(make_pair(s[i],i));
		}
	}
	int ans = 0;
	while(!pq.empty()){
		int w=pq.top().first;
		int i=pq.top().second;
		pq.pop();
		if(w<s[i]) continue;
		ans += mx-w;
		int p=i;
		while(p>3 && !m[p/2]){
			m[p]=1;
			p/=2;
		}
		m[p]=1;
		upd(p,mx-s[i]);
	}
	printf("%d\n",ans);
	return 0;
}