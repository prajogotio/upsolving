#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <iostream>
using namespace std;


int r[1000003], mark[1000003], l[1000003];
vector<int> S;
int N, C;
bool ok;
void build(int i, int L, int R) {
	printf("%d,%d,%d\n",i,L,R);
	if(!ok) return;
	if(i < L || R < i || L > R) {
		ok = false;
		return;
	}
	if(L==R) {
		S.push_back(i);
		return;
	}
	if(mark[i]) {
		build(L+1, L+1, max(l[i],min(r[i]-1,R)));
	}
	S.push_back(i);
	if(mark[i] && r[i]<=R){
		build(r[i], r[i], R);
	} else if(!mark[i]){
		build(L+1, L+1, R);
	}
}

int main(){
	int u,v;
	string type;
	scanf("%d%d",&N,&C);
	for(int i=1;i<=N;++i){
		r[i] = N+1;
	}
	for(int i=0;i<C;++i){
		scanf("%d%d",&u,&v);
		cin>>type;
		if(type == "RIGHT")
			r[u] = min(r[u],v);
		else {
			mark[u] = 1;
			l[u] = max(l[u],v);
		}
	}
	ok = true;
	build(1, 1, N);
	if(ok){
		for(int i=0;i<N;++i){
			if(i!=0)printf(" ");
			printf("%d",S[i]);
		}
		printf("\n");
	} else {
		printf("IMPOSSIBLE\n");
	}
	return 0;
}