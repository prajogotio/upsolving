#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

/*
  reducible iff sum s_i <= mt and max s_i <= t.
  proof by induction on sum s_i
*/

int a, b, n;
int l, t, m;
int main(){
	scanf("%d%d%d",&a,&b,&n);
	for(int i=0;i<n;++i){
		scanf("%d%d%d",&l,&t,&m);
		int lo = l, hi = (int)1e9, mid;
		while(lo<=hi){
			mid = (lo+hi)/2;
			long long val = 1LL*(2LL*a + 1LL*(l+mid-2)*b)*(mid-l+1)/2LL;
			if(1LL*a+1LL*b*(mid-1) > t ||
			   	val > 1LL*m*t) {
				hi = mid-1;
			} else {
				lo = mid+1;
			}
		}
		if(hi >= l) printf("%d\n",hi);
		else printf("-1\n");
	}
	return 0;
}