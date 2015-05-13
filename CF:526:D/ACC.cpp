#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
using namespace std;


int m[1000005];
int p[1000005];
int main(){
	int N, K;
	string s;
	scanf("%d%d",&N,&K);
	cin >> s;
	p[1] = 0;
	for(int i=2;i<=N;++i){
		int j = p[i-1];
		while(j!=0 && s[j]!=s[i-1]) j=p[j];
		if(s[j]==s[i-1])++j;
		p[i]=j;
	}
	for(int i=1;i<=N;++i){
		int slen = i-p[i];
		int tlen = i % slen;
		int scnt = i/slen;
		int AB = (scnt/K)*slen;
		int A = (scnt%K)*slen + tlen;
		m[i-1] = (AB>=A ? 1 : 0);
	}
	for(int i=0;i<N;++i){
		printf("%d",m[i]);
	}
	printf("\n");
	return 0;
}