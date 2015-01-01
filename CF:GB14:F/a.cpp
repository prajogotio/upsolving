#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
#include <cstring>
using namespace std;

int N,P;
int val[4003], cost[4003];
int h[4003], c[4003], t[4003];
int len[20003];			// height of the segment stack
int f[20003];			// index of upmost segment
int up[4003][4003];
int down[4003][4003];
vector<pair<int,int> > st;

int main(){
	int u,v,w;
	scanf("%d%d", &N, &P);
	for(int i=0;i<N;++i){
		scanf("%d%d%d", &u,&v,&w);
		cost[i] = u;
		val[i] = v;
		st.push_back(make_pair(w,i));
	}
	sort(st.begin(),st.end());
	memset(f, -1, sizeof f);
	for(int i=0;i<N;++i){
		len[st[i].first]++;
		len[st[i].first+P]--;
		h[i] = val[st[i].second];
		c[i] = cost[st[i].second];
		t[i] = st[i].first;
		f[st[i].first] = i;
		// printf("%d %d\n", st[i].first, st[i].second);
	}
	for(int i=0;i<N;++i){
		// printf("%d:h[%d] c[%d] t[%d]\n",i, h[i],c[i],t[i]);
	}
	for(int i=1;i<=20000;++i) {
		len[i] += len[i-1];
		f[i] = (f[i] == -1 && len[i]!=0 ? f[i-1] : f[i]);
	}
	// for(int i=0;i<=30;++i)printf("%2d ", i);printf("\n");
	// for(int i=0;i<=30;++i)printf("%2d ",len[i]);printf("\n");
	// for(int i=0;i<=30;++i)printf("%2d ",f[i]);printf("\n");
	for(int T=1;T<=20000;T+=P){
		if(f[T]==-1)continue;
		for(int b=0;b<=4000;++b){
			for(int i=f[T];i>f[T]-len[T];--i){
				if(b-c[i]>=0){
					if(i==f[T])up[b][i] = max(up[b][i], h[i]);
					else up[b][i] = max(up[b][i], up[b-c[i]][i+1]+h[i]);
				}
				if(i<f[T]) up[b][i] = max(up[b][i], up[b][i+1]);
			}
			for(int i=f[T]-len[T]+1;i<=f[T];++i){
				if(b-c[i]>=0){
					if(i==f[T]-len[T]+1)down[b][i] = max(down[b][i], h[i]);
					else down[b][i] = max(down[b][i], down[b-c[i]][i-1]+h[i]);
				}
				if(i>f[T]-len[T]+1)down[b][i] = max(down[b][i],down[b][i-1]);
			}
		}
		// printf("T[%d] f:%d len:%d, up[%d..%d], down[%d..%d]\n", T,f[T],len[T],f[T],f[T]-len[T]+1,f[T]-len[T]+1,f[T]);
	}
	int Q;
	scanf("%d", &Q);
	for(int qq=0;qq<Q;++qq){
		scanf("%d%d", &u,&v);
		int prev = ((u-1)/P)*P+1;
		int ans = 0;
		// printf("t=%d,b=%d,prev:%d,f:%d,len:%d\n",u,v,prev,f[u],len[u]);
		if(len[u]>0){
			for(int b=0;b<=v;++b){
				// printf("up[%d][%d]=%d, down[%d][%d]=%d\n",b,f[u]-len[u]+1,up[b][f[u]-len[u]+1],v-b,f[u],down[v-b][f[u]]);
				int tmp = 0;
				if(f[prev]>=f[u]-len[u]+1)tmp+=up[b][f[u]-len[u]+1];
				if(f[prev]<f[u])tmp+=down[v-b][f[u]];
				//printf("tmp:%d\n",tmp);
				ans = max(ans,tmp);
				
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}