#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;


int main(){
	int n;
	scanf("%d",&n);
	if(n<=2){
		printf("1\n1\n");
		return 0;
	} 
	if(n==3){
		printf("2\n1 3\n");
		return 0;
	}
	if(n==4){
		printf("4\n3 1 4 2\n");
		return 0;
	}
	printf("%d\n", n);
	for(int i=1;i<=n;i+=2)printf("%d ", i);
	for(int i=2;i<=n;i+=2)printf("%d ", i);
	printf("\n");
	return 0;
}