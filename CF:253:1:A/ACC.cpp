#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int mark[5][5];
int tot[10];
int N;

int main(){
	string s;
	scanf("%d",&N);
	int cnt = 0;
	for(int i=0;i<N;++i){
		cin >> s;
		int x;
		if(s[0] == 'G') x = 0;
		if(s[0] == 'B') x = 1;
		if(s[0] == 'R') x = 2;
		if(s[0] == 'Y') x = 3;
		if(s[0] == 'W') x = 4;
		mark[x][s[1]-'1'] = 1;
	}
	int mask = (1<<10) - 1;
	int ans = 11;
	while(mask>=0) {
		int k = 0;
		for(int i=0;i<10;++i){
			if(mask&(1<<i))++k;
		}
		bool ok = true;
		for(int a=0;a<5;++a){
			for(int b=0;b<5;++b){
				for(int c=0;c<5;++c){
					for(int d=0;d<5;++d){
						if(a==c && b==d)continue;
						if(mark[a][b] && mark[c][d]){
							if(a==c){
								if(!(mask&(1<<(b+5)) || mask&(1<<(d+5)))){
									ok = false;
								}
							} else {
								if(b==d){
									if(!((mask&(1<<a)) || (mask&(1<<c)))){
										ok = false;
									}
								}else{
									if(!((mask&(1<<a)) || (mask&(1<<c)) || (mask&(1<<(b+5))) || (mask&(1<<(d+5))))){
										ok = false;
									}
								}
							} 
						}
						if(!ok)break;
					}
				}
			}
		}
		if(ok){
			ans = min(ans,k);
		}
		--mask;
	}
	printf("%d\n",ans);
	return 0;
}