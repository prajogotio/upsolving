#include <iostream>
#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>
using namespace std;

vector<pair<int,int> > point;
vector<pair<long long, int> > valstack;
int N;
long long val[200005];
int segtree[1000000];

int rmq(int p, int S, int T, int L, int R) {
	if(S>T)return 0;
	if(T<L || R<S)return -1;
	if(S<=L && R<=T) return segtree[p];
	int M = (L+R)/2;
	int left = rmq(2*p, S, T, L, M);
	int right = rmq(2*p+1, S, T, M+1, R);
	return max(left, right);
}

void update(int p, int S, int L, int R, int val) {
	if(S < L || R < S) return;
	if(L == R && R == S) {
		segtree[p] = max(segtree[p],val);
		return;
	}
	int M = (L+R)/2;
	update(2*p, S, L, M, val);
	update(2*p+1, S, M+1, R, val);
	segtree[p] = max(segtree[2*p], segtree[2*p+1]);
	return;
}

//upperbound
int getIndex(long long V) {
	int lo = 0, hi = N-1, mid;
	while(lo <= hi) {
		mid = (lo+hi)/2;
		if(val[mid] <= V) {
			lo = mid+1;
		} else {
			hi = mid-1;
		}
	}
	if(lo == N || val[lo] > V) lo--;
	return lo;
}

void solve() {
	sort(point.begin(), point.end());

	for(int i=0;i<N;++i){
		val[i] = point[i].first+point[i].second;
		valstack.push_back(make_pair(val[i], i));
	}
	sort(valstack.begin(), valstack.end());
	for(int i=0;i<N;++i){
		val[i] = valstack[i].first;
	}
	for(int i=0;i<1000000;++i){
		segtree[i] = 0;
	}
	int ans = 0;
	for(int i=0;i<N;++i){
		long long d = point[i].first - point[i].second;
		long long v = point[i].first + point[i].second;
		int left = getIndex(d);
		int idx = getIndex(v);
		int prev = rmq(1, 0, left, 0, N-1);
		update(1, idx, 0, N-1, prev+1);
		ans = max(prev+1, ans);
	}
	printf("%d\n",ans);
}

int main(){
	scanf("%d",&N);
	int x, w;
	for(int i=0;i<N;++i){
		scanf("%d%d",&x,&w);
		point.push_back(make_pair(x,w));
	}
	solve();
	return 0;
}