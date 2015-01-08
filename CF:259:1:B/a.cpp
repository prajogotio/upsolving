#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
#include <utility>
using namespace std;

// b can be bigger than 30 

int g[32][32];
int dep[32];
int N, a[103];
map<pair<int,int>,int> dp;
map<pair<int,int>,int> par;
int gcd(int a, int b){
	if(a<b)swap(a,b);
	if(b==0)return a;
	return gcd(b,a%b);	
}
int iabs(int x){return x > 0 ? x : -x;}
int dfs(int k,int bm){
	if(k == N)return 0;
	if(dp.find(make_pair(k,bm))!=dp.end())return dp[make_pair(k,bm)];
	int ret = 123456;
	int ptr;
	for(int i=1;i<=30;++i){
		if(bm & dep[i])continue;
		int tmp = iabs(a[k]-i) + dfs(k+1,bm|(1<<(i-1)));
		if(ret > tmp){
			//printf("[%d,%d] %d->%d\n", k,i,ret, tmp);
			ret = tmp;
			ptr = i;
		}
	}
	dp[make_pair(k,bm)] = ret;
	par[make_pair(k,bm)] = ptr;
	return ret;
}
void print_ans(int u,int bm){
	int k = par[make_pair(u,bm)];
	if(u==N-1){
		printf("%d",k);
		return;
	}
	printf("%d ",k);
	print_ans(u+1,bm|(1<<(k-1)));
}
int main(){
	for(int i=1;i<=30;++i){
		for(int j=1;j<=30;++j){
			g[i][j] = gcd(i,j);
		}
	}
	for(int i=1;i<=30;++i){
		int tmp = 0;
		for(int j=30;j>=1;--j){
			tmp <<= 1;
			tmp += (g[i][j]>1?1:0);
		}
		dep[i] = tmp;
		//printf("%d: %d\n",i,tmp);
	}
	scanf("%d",&N);
	for(int i=0;i<N;++i)scanf("%d", &a[i]);
	int ret = dfs(0,0);
	//printf("%d\n",ret);
	print_ans(0,0);
	printf("\n");
	return 0;
}