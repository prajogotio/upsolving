#include <cstdio>
#include <cstdlib>
#include <ctime>
int vis[100003];
int main(){
	srand(time(NULL));
	printf("100000 100000\n");
	for(int i=0;i<100000;++i){
		printf("%d\n", rand()%2000000 + 1);
	}
	int u = 1;
	for(int i=2;i<=99999;++i){
		printf("%d %d\n", u, i);
		if(rand()%2)++u;
	}
	int ctr = 0;
	for(int i=1;i<=100000;++i){
		if(ctr < 50 && rand()%2){
			printf("2 %d %d\n", rand()%100000+1, rand()%2000000+1);
			++ctr;
		} else {
			printf("1 %d\n", rand()%100000+1);
		}
	}
	return 0;
}