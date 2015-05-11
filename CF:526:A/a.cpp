#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;

string s;

int main(){
	int N;
	scanf("%d",&N);
	cin >> s;
	for(int k=1;k<100;++k){
		for(int i=0;i<N;++i){
			bool ok = true;
			int cnt = 0;
			for(int j=i;j<N && cnt<5;j+=k){
				if(s[j]=='.'){
					ok = false;
					break;
				} else {
					++cnt;
				}
			}
			if(ok && cnt==5) {
				printf("yes\n");
				return 0;
			}
		}
	}
	printf("no\n");
	return 0;
}