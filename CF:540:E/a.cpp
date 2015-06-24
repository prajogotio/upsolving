#include <iostream>
#include <algorithm>
#include <cstdio>
#include <map>
#include <vector>
#include <utility>
#include <map>
using namespace std;

namespace codeforces {

int a[400010];
int pos[400010], val[400010], len[400010];
long long seg[4*400010];
map<int,int> m;
int n;
vector<pair<int,int> > v;
int sz;

void update(int p, int L, int R, int S, int val) {
	if(R < S || S < L) return;
	if(L==R && R==S) {
		seg[p] = val;
		return;
	}
	int M = (L+R)/2;
	update(2*p, L, M, S, val);
	update(2*p+1, M+1, R, S, val);
	seg[p] = seg[2*p] + seg[2*p+1];
}

long long rmq(int p, int L, int R, int S, int T) {
	if (R<S || T<L) return 0;
	if (S<= L && R <= T) {
		return seg[p];
	}
	int M = (L+R)/2;
	return rmq(2*p, L, M, S, T) + rmq(2*p+1, M+1, R, S, T);
}


void set(int i, int val) {
	update(1, 1, sz, i, val);
}

long long smaller(int i, int j) {
	return rmq(1, 1, sz, i, j);
}

void solve() {
	scanf("%d",&n);
	int x,y;
	vector<int> st;
	for(int i=0;i<n;++i){
		scanf("%d%d",&x,&y);
		v.push_back(make_pair(x,y));
		st.push_back(x);
		st.push_back(y);
	}
	sort(st.begin(), st.end());
	int idx = 1;
	int prev = 1;
	m[1] = idx;
	val[idx] = 1;
	len[1] = 1;
	++idx;
	for(int i=0;i<2*n;++i){
		if(st[i] == prev) continue;
		if(prev+1 < st[i]) {
			m[prev+1] = idx;
			val[idx] = prev+1;
			len[idx] = st[i] - prev - 1;
			++idx;
		}
		prev = st[i];
		m[st[i]] = idx;
		val[idx] = st[i];
		len[idx] = 1;
		++idx;
	}
	for(int i=1;i<idx;++i){
		pos[i] = i;
	}
	for(int i=0;i<n;++i){
		swap(pos[m[v[i].first]], pos[m[v[i].second]]);
	}
	long long ans = 0;
	sz = idx-1;
	for(int i=1;i<=sz;++i){
		int cur = val[pos[i]];
		ans += 1LL * len[i] * ((long long)cur - 1LL - smaller(1,pos[i]));
		set(pos[i], len[i]);
	}
	cout << ans << endl;
}

}

int main(){
	codeforces::solve();
	return 0;
}

