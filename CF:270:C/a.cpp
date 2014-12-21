#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;

string s[100005][2];

int main(){
	int n;
	scanf("%d", &n);
	for(int i=0;i<n;++i){
		cin >> s[i][0] >> s[i][1];
	}
	int prev, k;
	int cur;
	scanf("%d", &cur);
	prev = cur-1;
	k = (s[prev][0] > s[prev][1] ? 1 : 0);
	bool ok = true;
	for(int i=1;i<n;++i){
		scanf("%d", &cur);
		int state = 0;
		if(s[prev][k] <= s[cur-1][0]){
			state = 1;
		}
		if(s[prev][k] <= s[cur-1][1]){
			state += 2;
		}
		if(!state) {
			ok = false;
			break;
		}
		if(state == 1){
			prev = cur-1;
			k = 0;
		}
		if(state == 2){
			prev = cur-1;
			k = 1;
		}
		if(state == 3){
			prev = cur-1;
			k = (s[prev][0] < s[prev][1] ? 0 : 1);
		}
	}
	if(ok){
		printf("YES\n");
	} else {
		printf("NO\n");
	}
	return 0;
}