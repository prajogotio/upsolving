#include <cstdio>

// wrong idea

int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	int _i = 0;
	int i = 1;
	int j = 0;
	while(i+j<=m){
		i+=j;
		_i=i;
		++j;
	}
	int mark[53];
	for(int k=0;k<53;++k)mark[k]=0;
	for(int k=1;k<n-j;++k){
		printf("%d ",k);
		mark[k] = 1;
	}
	int x = n-j+m-_i;
	bool flag = false;
	if(x){
		printf("%d",x);
		flag = true;
	}
	mark[x]=1;
	for(int k=n;k>=1;--k){
		if(mark[k]==0){
			if(flag) printf(" ");
			printf("%d",k);
			flag = true;
		}
	}
	printf("\n");
	return 0;

}