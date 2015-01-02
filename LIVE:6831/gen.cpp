#include <cstdio>
#include <ctime>
#include <cstdlib>

int mark[1000003];
int seat[1000003];

int main(){
	srand(time(NULL));
	int N=12, M=5;
	printf("%d %d\n", N, M);
	for(int i=0;i<M;++i){
		int u = rand()%N;
		int v = rand()%N;
		while(mark[u])u = rand()%N;
		while(seat[v])v = rand()%N;
		mark[u] = 1;
		seat[v] = 1;
		printf("%d %d\n", u+1, v+1);
	}
	return 0;
}