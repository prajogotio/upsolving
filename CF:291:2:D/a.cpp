#include <cstdio>
#include <algorithm>
using namespace std;


// WRONG IDEA, WRONG INTUITION, WRONG UNDERSTANDING

int n, m, k;
int a[100005][6];
long long s[100005];



int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;++i){
		for(int j=0;j<m;++j){
			scanf("%d",&a[i][j]);
		}
	}
	int ans = 0;
	for(int b=1;b<(1<<m);++b){
		s[0] = 0;
		for(int i=1;i<=n;++i){
			long long val = 0;
			for(int j=0;j<m;++j){
				if(b&(1<<j))val+=a[i][j];
			}
			s[i] = s[i-1] + val;
		}
		for(int i=1;i<=n;++i){
			int lo = 0, hi = i, mid;
			while(lo <= hi) {
				mid = (lo+hi)/2;
				if(s[i]-s[mid]<=k){
					hi=mid-1;
				}else{
					lo=mid+1;
				}
			}
			ans = max(ans,i-lo);
		}
	}
	printf("%d\n",ans);
	return 0;
}