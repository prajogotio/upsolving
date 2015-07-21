#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
int n;
int a[2000010];
int seg[4*200010];
int lo[200010];
int hi[200010];
vector<pair<int,int> > stack;
int maxval[200010];
int sentinel;
void init(int p, int l, int r, int val){
	if(p==1){
		sentinel = val;
	}
	if(l==r) {
		seg[p] = val;
		return;
	}
	int m = (l+r)/2;
	init(2*p,l,m,val); 
	init(2*p+1,m+1,r,val);
	seg[p]=val;
}

void initmaxval(int p, int l, int r){
	if(l==r) {
		seg[p] = maxval[l];
		return;
	}
	int m = (l+r)/2;
	initmaxval(2*p,l,m); 
	initmaxval(2*p+1, m+1, r);
	seg[p]=max(seg[2*p],seg[2*p+1]);
}

void upd(int p, int l, int r, int s, int val){
	if(r<s || s<l) return;
	if(s==l && l==r) {
		seg[p] = val;
		return;
	}
	int m = (l+r)/2;
	upd(2*p,l,m,s,val);
	upd(2*p+1,m+1,r,s,val);
	seg[p] = max(seg[2*p],seg[2*p+1]);
}

int rmq(int p, int l, int r, int s, int t){
	if(r<s || t<l) return sentinel;
	if(s<=l && r<=t) return seg[p];
	int m = (l+r)/2;
	int left = rmq(2*p, l, m, s, t);
	int right = rmq(2*p+1, m+1, r, s, t);
	return max(left, right);
}


int main(){
	scanf("%d",&n);

	for(int i=0;i<n;++i){
		scanf("%d",&a[i]);
		stack.push_back(make_pair(a[i],i));
	}

	sort(stack.begin(), stack.end());
	init(1,0,n-1,-1);
	int prev=0;
	for(int cur=0;cur<n;++cur){
		if(stack[cur].first!=stack[prev].first){
			while(prev<cur){
				upd(1,0,n-1,stack[prev].second,stack[prev].second);
				++prev;
			}
		}
		lo[cur] = rmq(1,0,n-1,0,stack[cur].second);
		//printf("lo[%d]=%d, a[%d]=%d\n",cur,lo[cur],stack[cur].second,stack[cur].first);
	}
	init(1,0,n-1,-n);
	prev=0;
	for(int cur=0;cur<n;++cur){
		if(stack[cur].first!=stack[prev].first){
			while(prev<cur){
				upd(1,0,n-1,stack[prev].second,-stack[prev].second);
				++prev;
			}
		}
		hi[cur] = -rmq(1,0,n-1,stack[cur].second,n-1);
		//printf("hi[%d]=%d, a[%d]=%d\n",cur,hi[cur],stack[cur].second,stack[cur].first);

	}
	for(int i=0;i<n;++i){
		int len = hi[i]-lo[i]-1;
		maxval[len] = max(maxval[len], stack[i].first);

	}
	initmaxval(1,1,n);
	for(int i=1;i<=n;++i){
		printf("%d ",rmq(1,1,n,i,n));
	}
	printf("\n");
	return 0;
}