#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <utility>
using namespace std;

int N;
map<int, pair<int,int> > S;
int segtree[2000003];
int mark[500003];
int cnt[500003];
int a[500003];
vector<int> st;

void build(int p, int L, int R){
	if(L==R){
		segtree[p] = mark[L];
		return;
	}
	int M = (L+R)/2;
	build(2*p, L, M);
	build(2*p+1, M+1, R);
	segtree[p] = min(segtree[p], segtree[2*p]);
}

int rmq(int p, int L, int R, int S, int T){
	if(R < S || T < L) return -1;
	if(S <= L && R <= T){
		return segtree[p];
	}
	int M = (L+R)/2;
	int left = rmq(2*p, L, M, S, T);
	int right = rmq(2*p+1, M+1, R, S, T);
	if(left < 0) return right;
	if(right < 0) return left;
	return min(left, right);
}

int update(int p, int L, int R, int S, int T){
	if(R < S || T < L) return rmq(p, L, R, L, R);
	if(S <= L && R <= T){
		segtree[p] = mark[L];
		return segtree[p];
	}
	int M = (L+R)/2;
	int left = update(2*p, L, M, S, T);
	int right = update(2*p+1, M+1, R, S, T);
	return (segtree[p] = min(left, right));
}

int main(){
	scanf("%d", &N);
	int u, v;
	int ans = 0;
	for(int i=0;i<N;++i)mark[i] = i;
	build(1, 0, N-1);
	for(int i=0;i<N;++i){
		scanf("%d", &u);
		a[i] = u;
		if(S.find(u) != S.end()){
			if(S[u].second == -1){
				S[u].second = i;
				mark[S[u].second] = S[u].first;
				update(1, 0, N-1, S[u].second, S[u].second);
			} else {
				S[u].second = i;
				mark[i] = S[u].first;
				update(1, 0, N-1, i, i);
			}
			cnt[S[u].first]++;
			if ((v = rmq(1, 0, N-1, S[u].first, S[u].second)) < S[u].first){
				++ans;
				st.push_back(u);
				st.push_back(a[v]);
				S.clear();
			} else if(cnt[S[u].first] == 3){
				st.push_back(u);
				st.push_back(u);
				++ans;
				S.clear();
			}
		} else {
			S[u] = make_pair(i, -1);
			update(1,0,N-1,i,i);
		}
	}
	printf("%d\n", ans*4);
	if(ans == 0) return 0;
	for(int i=0;i<ans;++i){
		if(i!=0)printf(" ");
		printf("%d %d %d %d", st[2*i+1], st[2*i], st[2*i+1], st[2*i]);
	}
	printf("\n");
	return 0;
}