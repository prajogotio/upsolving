#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

/* READ WRONGLY */

int card[103][2];
int mark[5][5];
int N;

int main(){
	string s;
	scanf("%d",&N);
	for(int i=0;i<N;++i){
		cin >> s;
		if(s[0] == 'G') card[i][0] = 0;
		if(s[0] == 'B') card[i][0] = 1;
		if(s[0] == 'R') card[i][0] = 2;
		if(s[0] == 'Y') card[i][0] = 3;
		if(s[0] == 'W') card[i][0] = 4;
		card[i][1] = s[1] - '1' + 5;
		mark[card[i][0]][card[i][1]-5] = 1;
	}
	int mask = (1<<10) - 1;
	int ans = 11;
	while(mask>=0) {
		int k = 0;
		int check[5][5];
		for(int i=0;i<5;++i)
			for(int j=0;j<5;++j)
				check[i][j] = 0;
		for(int i=0;i<10;++i){
			if(mask&(1<<i)) ++k;
		}
		for(int i=0;i<N;++i){
			if( (mask & (1 << card[i][0])) || (mask & (1 << card[i][1])) ) {
				check[card[i][0]][card[i][1]-5] = 1;
			}
		}
		int cnt = 0;
		for(int i=0;i<5;++i)
			for(int j=0;j<5;++j)
				if(check[i][j] != mark[i][j]) {
					++cnt;
				}
		if(cnt <= 1){
			ans = min(ans, k);
		}
		--mask;
	}
	printf("%d\n",ans);
	return 0;
}