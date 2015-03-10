#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>
#include <cassert>
using namespace std;



int INF = 12345678;
long long MOD = (long long) 1e9 + 9LL;
int tree[400005][2];

map<pair<long long,long long>,int> ptr;
int support[100005];
vector<pair<long long,long long> > coor;
int in_tree[100005], used[100005];
int M;


void update(int p, int S, int L, int R, int val) {
	if(S < L || R < S) return;
	if(L == R && R == S) {
		if(val == 0) {
			tree[p][0] = -1;
			tree[p][1] = INF;
		} else {
			tree[p][0] = S;
			tree[p][1] = S;
		}
		return;
	}
	int M = (L+R)/2;
	update(2*p, S, L, M, val);
	update(2*p+1, S, M+1, R, val);
	tree[p][0] = max(tree[2*p][0], tree[2*p+1][0]);
	tree[p][1] = min(tree[2*p][1], tree[2*p+1][1]);
}

int rmaxq(int p, int S, int T, int L, int R) {
	if(T < L || R < S) return -1;
	if(S <= L && R <= T) return tree[p][0];
	int M = (L+R)/2;
	int left = rmaxq(2*p, S, T, L, M);
	int right = rmaxq(2*p+1, S, T, M+1, R);
	return max(left, right);
}

int rminq(int p, int S, int T, int L, int R) {
	if(T < L || R < S) return INF;
	if(S <= L && R <= T) return tree[p][1];
	int M = (L+R)/2;
	int left = rmaxq(2*p, S, T, L, M);
	int right = rmaxq(2*p+1, S, T, M+1, R);
	return min(left, right);
}

void build(int p, int L, int R) {
	if(L==R) {
		tree[p][0] = -1;
		tree[p][1] = INF;
		return;
	}
	int M = (L+R)/2;
	build(2*p, L, M);
	build(2*p+1,M+1,R);
	tree[p][0] = -1;
	tree[p][1] = INF;
}

int supportedBy(long long x, long long y) {
	if(ptr.count(make_pair(x,y))) {
		return support[ptr[make_pair(x,y)]];
	}
	return INF;
}

bool isRemovable(int u) {
	long long x = coor[u].first;
	long long y = coor[u].second;
	return supportedBy(x-1,y+1) > 1 && supportedBy(x,y+1) > 1 && supportedBy(x+1,y+1) > 1;
}

void insert_to_tree(int u) {
	if(used[u])return;
	if(in_tree[u]) return;
	in_tree[u] = 1;
	update(1, u, 0, M-1, 1);
}

void remove_from_tree(int u) {
	if(used[u])return;
	if(in_tree[u] == 0) return;
	in_tree[u] = 0;
	update(1, u, 0, M-1, 0);
}

void remove_support(long long x, long long y) {
	if(ptr.count(make_pair(x,y))){
		support[ptr[make_pair(x,y)]]--;
	}
}

void revalidate(long long x, long long y) {
	if(ptr.count(make_pair(x,y))){
		int u = ptr[make_pair(x,y)];
		if(isRemovable(u)) {
			insert_to_tree(u);
		} else {
			remove_from_tree(u);
		}
	}
}

void add_support(long long x, long long y) {
	if(ptr.count(make_pair(x,y))){
		support[ptr[make_pair(x,y)]]++;
	}
}

int main(){
	scanf("%d",&M);
	long long x, y;
	for(int i=0;i<M;++i){
		cin >> x >> y;
		coor.push_back(make_pair(x,y));
		ptr[make_pair(x,y)] = i;
	}

	build(1, 0, M-1);

	for(int i=0;i<M;++i){
		x = coor[i].first;
		y = coor[i].second;
		add_support(x-1,y+1);
		add_support(x,y+1);
		add_support(x+1,y+1);
	}

	for(int i=0;i<M;++i){
		if(isRemovable(i)) {
			insert_to_tree(i);
		}
	}

	int ans[100005];

	for(int cur = 0; cur < M; ++cur) {
		int u;
		if(cur % 2) {
			u = rminq(1, 0, M-1, 0, M-1);
		} else {
			u = rmaxq(1, 0, M-1, 0, M-1);
		}
		assert(u!=-1 && u != INF);
		x = coor[u].first;
		y = coor[u].second;
		ans[cur] = u;
		remove_from_tree(u);
		used[u] = 1;
		support[u] = INF;
		remove_support(x-1,y+1);
		remove_support(x, y+1);
		remove_support(x+1, y+1);
		revalidate(x-2,y);
		revalidate(x-1,y);
		revalidate(x+1,y);
		revalidate(x+2,y);
		revalidate(x,y-1);
		revalidate(x-1,y-1);
		revalidate(x+1,y-1);
	}
	long long sum = 0;
	for(int i=0;i<M;++i){
		sum *= M;
		sum %= MOD;
		sum += ans[i];
		sum %= MOD;
	}
	cout << sum << endl;
}
