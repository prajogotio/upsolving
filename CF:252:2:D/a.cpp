#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int a[3003];
int p[3003];
int ff[3003];
int pos[3003];
int vis[3003];
int n,m;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i){
		scanf("%d",&a[i]);
		p[a[i]] = i;
	}
	scanf("%d",&m);
	int col = 0;
	int sum = 0;
	for(int i=1;i<=n;++i){
		if(ff[i] == 0){
			++col;
			int cnt = 0;
			int cur = i;
			int root = cur;
			while(1) {
				++cnt;
				ff[cur] = col;
				cur = p[cur];
				if(cur == root) break;
			}
			pos[col] = i;
			sum += (cnt-1);
		}
	}
	if(sum == m) {
		printf("0\n");
	} else if(sum > m) {
		//break down ff
		int k = sum - m;
		printf("%d\n",k);
		bool flag = false;
		for(int i=1;i<=n;++i){
			while(i != p[i]){
				int cur = p[i];
				int root = i;
				int smallest = 3005;
				while(cur != root) {
					if(smallest > cur){
						smallest = cur;
					}
					cur = p[cur];
				}
				int x,y,u,v;
				x = i;
				y = smallest;
				u = a[x];
				v = a[y];
				p[u] = y;
				p[v] = x;
				a[x] = v;
				a[y] = u;
				if(flag)printf(" ");
				printf("%d %d",x,y);
				--k;
				if(!flag) flag = true;
				if(k==0)break;

			}
			if(k==0)break;
		}
		printf("\n");
	} else {
		//merge ff
		int k = m-sum;
		printf("%d\n",k);
		bool flag = false;
		vis[1] = 1;
		for(int i=1;i<=n;++i){
			if(vis[ff[i]])continue;
			vis[ff[i]] = 1;
			if(flag)printf(" ");
			printf("1 %d", pos[ff[i]]);
			if(!flag)flag=true;
			--k;
			if(k==0)break;
		}
		printf("\n");
	}
	return 0;
}