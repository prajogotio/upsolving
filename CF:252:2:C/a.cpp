#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int N, M, K;


int main(){
	scanf("%d%d%d",&N,&M,&K);
	int x = 1, y = 1;
	int state = 0;
	for(int i=0;i<K-1;++i){
		printf("2");
		printf(" %d %d", x,y);
		if(state==0){
			y++;
			if(y>M) {
				y--;
				state = 1;
				x++;
			}
		} else {
			y--;
			if(y==0){
				y++;
				x++;
				state = 0;
			}
		}
		printf(" %d %d", x,y);
		if(state==0){
			y++;
			if(y>M) {
				y--;
				state = 1;
				x++;
			}
		} else {
			y--;
			if(y==0){
				y++;
				x++;
				state = 0;
			}
		}
		printf("\n");
	}
	printf("%d", N*M-2*(K-1));
	for(int i=0;i<N*M-2*(K-1);++i){
		printf(" %d %d", x,y);
		if(state==0){
			y++;
			if(y>M) {
				y--;
				state = 1;
				x++;
			}
		} else {
			y--;
			if(y==0){
				y++;
				x++;
				state = 0;
			}
		}
	}
	printf("\n");
	return 0;
}