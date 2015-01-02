#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <cstring>
using namespace std;

int fix[1000003];
int filled[1000003];
int vis[1000003];
int K, D;
long long ans;
long long MOD = 1000000007LL;

int main(){
	int u,v;
	while(scanf(" %d %d", &K,&D)!=EOF){
		ans = 1;
		memset(filled, 0, sizeof filled);
		memset(fix, 0,sizeof fix);
		memset(vis, 0, sizeof vis);
		for(int i=0;i<D;++i){
			scanf(" %d %d", &u, &v);
			filled[v] = u;
			fix[u] = 1;
		}
		// for(int i=1;i<=K;++i)printf("%2d ", i);printf("\n");
		// for(int i=1;i<=K;++i)printf("%2d ", filled[i]);printf("\n");
		// for(int i=1;i<=K;++i)printf("%2d ", fix[i]);printf("\n");
		int balance = 0;
		int beg = 1;
		int state = 0;
		for(int j=1;j<=2*K;++j){
			int i = (j>K?j-K:j);
			if(!state){
				if(!fix[i] && filled[i]){
					beg = j;
					state = 1;
					balance ++;
				}
			} else {
				if(fix[i]) --balance;
				if(filled[i]) ++balance;
				if(balance<0){
					beg = -1;
					state = 0;
					balance = 0;
				} else if(balance == 0 && j-beg+1 == K){
					break;
				}
			}
		}
		// printf("%d\n",beg);
		long long cnt = 0;
		for(int j=beg;j<=2*K;++j){
			int i = (j>K?j-K:j);
			if(vis[i])break;
			vis[i] = 1;
			if(!fix[i])++cnt;
			if(!filled[i] && cnt != 0){
				assert(cnt != 0);
				ans *= cnt;
				ans %= MOD;
				--cnt;
			}
		}
		cout << ans << endl;
	}
	return 0;
}