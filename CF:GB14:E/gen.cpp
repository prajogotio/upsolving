#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main(){
	srand(time(NULL));
	printf("200000\n");
	int prev = 1;
	for(int i=0;i<200000;++i){
		int tmp = rand()%2000 + 1;
		printf("%d %d\n", prev + tmp, rand() % 10000000 + 1);
		prev += tmp;
	}
	printf("200000\n");
	for(int i=0;i<100;++i){
		int u = rand()%200000+1;
		printf("%d %d\n", u, max(200000,u+rand()%50000));
	}
	return 0;
}