#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;


int N, M, K, Q;
vector<pair<pair<int,int>,pair<int,int> > > square;
vector<pair<int,int> > point;
int mark[200005];
int a[200005];
int seg[400005];

int rmq(int p, int S, int T, int L, int R) {
	if(R<S || T<L)return -1;
	if(S<=L && R<=T){
		return seg[p];
	}
	int M = (L+R)/2;
	int left = rmq(2*p,S,T,L,M);
	int right = rmq(2*p+1,S,T,M+1,R);
	if(left==-1)return right;
	if(right==-1)return left;
	// printf("rmq [%d,%d,%d,%d,%d][%d,%d]\n",p,S,T,L,R,left,right);
	return min(left,right);
}

void upd(int p, int L, int R, int S){
	if(R<S || S<L) return;
	if(L==R && R == S){
		seg[p] = a[S];
		return;
	}
	int M = (L+R)/2;
	upd(2*p,L,M,S);
	upd(2*p+1,M+1,R,S);
	seg[p] = min(seg[2*p+1],seg[2*p]);
}

bool cmp(const pair<int,int>& L, const pair<int,int>& R) {
	if(R.second == L.second) {
		return L.first < R.first;
	}
	return L.second < R.second;
}

void solve() {
	// sorted by x
	sort(point.begin(), point.end());
	vector<pair<int,int> > st;
	for(int i=0;i<Q;++i){
		st.push_back(make_pair(square[i].second.first, i));
	}
	sort(st.begin(), st.end());
	int next = 0;
	for(int i=0;i<Q;++i){
		int cur = st[i].second;
		//printf("%d,%d - %d,%d\n",square[cur].first.first, square[cur].first.second,
		//						square[cur].second.first, square[cur].second.second);
		//printf("limit: %d\n",st[i].first);
		while(next < K && point[next].first <= st[i].first){
			int x = point[next].first;
			int y = point[next].second;
			//printf("consider %d %d\n",x,y);
			a[y] = max(a[y], x);
			upd(1, 1, M, y);
			++next;
			//for(int i=1;i<=M;++i)printf("%d ", a[i]);printf("\n");
		}
		int y1 = square[cur].first.second;
		int y2 = square[cur].second.second;
		int x1 = square[cur].first.first;
		int low = rmq(1,y1,y2,1,M);
		//printf("[%d,%d] == %d >= %d?\n",y1,y2,low,x1);
		if(low >= x1) {
			mark[cur]++;
		}
	}

	// sort by y
	sort(point.begin(), point.end(), cmp);
	st.clear();
	for(int i=0;i<=N;++i)a[i]=0;
	for(int i=0;i<=4*N;++i)seg[i]=0;
	for(int i=0;i<Q;++i){
		st.push_back(make_pair(square[i].second.second, i));
	}
	sort(st.begin(), st.end());
	next = 0;
	for(int i=0;i<Q;++i){
		int cur = st[i].second;
		while(next < K && point[next].second <= st[i].first){
			int x = point[next].first;
			int y = point[next].second;
			a[x] = max(a[x], y);
			upd(1, 1, N, x);
			++next;
		}
		int x1 = square[cur].first.first;
		int x2 = square[cur].second.first;
		int y1 = square[cur].first.second;
		if(rmq(1,x1,x2,1,N) >= y1) {
			mark[cur]++;
		}
	}
	for (int i=0;i<Q;++i){
		if(mark[i]>0)printf("YES\n");
		else printf("NO\n");
	}
}

int main(){
	scanf("%d%d%d%d",&N,&M,&K,&Q);
	int x,y;
	for(int i=0;i<K;++i){
		scanf("%d%d",&x,&y);
		point.push_back(make_pair(x,y));
	}
	int x1,y1;
	for(int i=0;i<Q;++i){
		scanf("%d%d%d%d",&x,&y,&x1,&y1);
		square.push_back(make_pair(make_pair(x,y),make_pair(x1,y1)));
	}
	solve();
	return 0;
}