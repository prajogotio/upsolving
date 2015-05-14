#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N = 300005;
int minv[4*N], cnt[4*N], add[4*N];
int loq[N], hiq[N];
int a[N];
int n;

void init(int p, int L, int R){
	cnt[p] = 1;
	minv[p] = L;
	add[p] = 0;
	if(L==R){
		return;
	}
	int M = (L+R)/2;
	init(2*p, L, M);
	init(2*p+1, M+1, R);
}

void upd(int p, int L, int R, int S, int T, int val){
	if(R<S || T<L) return;
	if(S <= L && R <= T) {
		add[p] += val;
		return;
	}
	if(add[p]){
		add[2*p] += add[p];
		add[2*p+1] += add[p];
		add[p] = 0;
	}
	int M = (L+R)/2;
	upd(2*p, L, M, S, T, val);
	upd(2*p+1, M+1, R, S, T, val);
	minv[p] = min(minv[2*p]+add[2*p], minv[2*p+1]+add[2*p+1]);
	cnt[p] = 0;
	if(minv[p] == minv[2*p]+add[2*p]){
		cnt[p] += cnt[2*p];
	}
	if(minv[p] == minv[2*p+1]+add[2*p+1]){
		cnt[p] += cnt[2*p+1];
	}
}

int main(){
	scanf("%d",&n);
	int x,y;
	for(int i=0;i<n;++i){
		scanf("%d%d",&x,&y);
		a[x] = y;
	}
	int lo=0, hi=0;
	long long ans = 0;
	init(1, 1, n);
	//for(int i=1;i<=n;++i)printf("%d ",a[i]);printf("\n");
	for(int i=1;i<=n;++i){
		while(hi>0 && a[i] > a[hiq[hi]]){
			int from = (hi-1 == 0) ? 1 : hiq[hi-1]+1;
			int to = hiq[hi];
			//printf("[%d] hi %d, from[%d], to[%d], val[%d]\n",i, hiq[hi], from, to, -a[hiq[hi]]);
			upd(1, 1, n, from, to, -a[hiq[hi]]);
			hi--;
		}
		hiq[++hi]=i;
		while(lo>0 && a[i] < a[loq[lo]]) {
			int from = (lo-1 == 0) ? 1 : loq[lo-1]+1;
			int to = loq[lo];
			upd(1, 1, n, from, to, +a[loq[lo]]);
			//printf("[%d] lo %d, from[%d], to[%d], val[%d]\n",i, loq[lo], from, to, a[loq[lo]]);
			lo--;
		}
		loq[++lo]=i;
		upd(1, 1, n, (hi-1 == 0 ? 1 : hiq[hi-1]+1), i, a[i]);
		upd(1, 1, n, (lo-1 == 0 ? 1 : loq[lo-1]+1), i, -a[i]);
		upd(1, 1, n, 1, i-1, -1);
		upd(1, 1, n, i, i, -i);
		if(minv[1] + add[1] == 0) ans += cnt[1];
		//printf("so far: %d\n",(int)ans);
	}
	cout << ans << endl;
	return 0;
}