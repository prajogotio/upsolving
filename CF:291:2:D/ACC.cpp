#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int segtree[400005][6];
int cache[400005][6];
int a[100005][6];
int N,M,K;

void build(int p, int L, int R) {
	if(L==R){
		for(int i=0;i<M;++i){
			segtree[p][i] = a[L][i];
		}
		return;
	}
	int mid = (L+R)/2;
	build(2*p,L,mid);
	build(2*p+1,mid+1,R);
	for(int i=0;i<M;++i){
		segtree[p][i]=max(segtree[2*p][i],segtree[2*p+1][i]);
	}
}

int rmq(int p,int L,int R,int S,int T){
	if(R<S || T<L)return -1;
	if(S<=L && R<=T){
		for(int i=0;i<M;++i){
			cache[p][i]=segtree[p][i];
		}
		return p;
	}
	int mid=(L+R)/2;
	int left = rmq(2*p,L,mid,S,T);
	int right = rmq(2*p+1,mid+1,R,S,T);
	if(left==-1)return right;
	if(right==-1)return left;
	for(int i=0;i<M;++i){
		cache[p][i] = max(cache[left][i],cache[right][i]);
	}
	return p;
}

int main(){
	scanf("%d%d%d",&N,&M,&K);
	for(int i=0;i<N;++i){
		for(int j=0;j<M;++j){
			scanf("%d",&a[i][j]);
		}
	}
	build(1,0,N-1);
	int ans = -1;
	int b[6] = {0,0,0,0,0,0};
	for(int i=0;i<N;++i){
		int lo=0,hi=i,mid;
		while(lo<=hi){
			mid=(lo+hi)/2;
			int val = 0;
			int x = rmq(1,0,N-1,mid,i);
			for(int j=0;j<M;++j){
				val += cache[x][j];
			}
			if(val <= K){
				hi=mid-1;
				if(ans < i-mid+1){
					ans = i-mid+1;
					for(int j=0;j<M;++j)b[j]=cache[x][j];
				}
			}else{
				lo=mid+1;
			}
		}
	}
	for(int j=0;j<M;++j){
		if(j!=0)printf(" ");
		printf("%d",b[j]);
	}
	printf("\n");
	return 0;
}