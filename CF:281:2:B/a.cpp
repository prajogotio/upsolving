#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> a[2];
long long sum[2];
int last;

int main(){
	int N;
	scanf("%d", &N);
	int u;
	for(int i=0;i<N;++i){
		scanf("%d", &u);
		if(u>0){
			a[0].push_back(u);
			sum[0] += u;
			last = 0;
		} else {
			a[1].push_back(-u);
			sum[1] += -u;
			last = 1;
		}
	}

	if(sum[0] > sum[1]){
		printf("first\n");
	} else if (sum[0] < sum[1]) {
		printf("second\n");
	} else {
		int state = 0;
		for(int i=0;i<min(a[0].size(), a[1].size());++i){
			if(a[0][i] > a[1][i]) state = 1;
			else if(a[0][i] < a[1][i]) state = -1;
			if(state != 0) break;
		}
		if(state == 0) {
			if(a[0].size() > a[1].size()) state = 1;
			else if(a[0].size() < a[1].size()) state = -1;
			else {
				state = (last == 0 ? 1 : -1);
			}
		}
		if(state == 1) printf("first\n");
		else printf("second\n");
	}
	return 0;
}