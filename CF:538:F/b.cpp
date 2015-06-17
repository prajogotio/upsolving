#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

vector<pair<int,int> > s;
long long b[200010];
int seg[4*200010];
int n;
int p, q;

void upd(int p, int L, int R, int S, int val) {
	if (R < S || S < L) return;
	if (L == R && R == S) {
		seg[p] = val;
		return;
	}
	int M = (L+R)/2;
	upd(p+p, L, M, S, val);
	upd(p+p+1, M+1, R, S, val);
	seg[p] = seg[p+p] + seg[p+p+1];
}

int rmq(int p, int L, int R, int S, int T) {
	if (R<S || T<L) return 0;
	if (S <= L && R <= T) return seg[p];
	int M = (L+R)/2;
	return rmq(2*p, L, M, S, T) + rmq(2*p+1, M+1, R, S, T);
}

void add() {
	upd(1, 1, n, s[q].second, 1);
}

int cmp(int left, int right) {
	return rmq(1, 1, n, left, right);
}

void count() {
	int v = s[p].second;
	for (int k = 1; k < n && (v-1)*k+2 <= n; ++k) {
		int left = max(v, (v-1) * k + 2);
		int right = min(v*k + 1, n);
		if (left > right) continue;
		b[k] += right - left + 1 - cmp(left, right);
	}
}

bool next() {
	if(p >= n) return false;
	if(p == q) {
		int cur = s[q].first;
		while(q < n && s[q].first == cur) {
			add();
			++q;
		}
	}
	count();
	++p;
	return true;
}


int main(){
	scanf("%d",&n);
	int v;
	for(int i=1;i<=n;++i){
		scanf("%d",&v);
		s.push_back(make_pair(v, i));
	}
	sort(s.begin(), s.end());
	reverse(s.begin(), s.end());
	p = q = 0;
	while (next());
	for(int i=1;i<n;++i){
		cout << b[i] << " ";
	}
	printf("\n");
	return 0;
}