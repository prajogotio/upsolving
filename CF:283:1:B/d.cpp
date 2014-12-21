#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

int sum[100003];
int _sum[100003];
int a[100003];
vector<pair<int,int> > st;
int N;

int bsearch(int * s, int val, int margin){
	int lo = 0, hi = N-1, mid;
	while(lo <= hi){
		mid = (lo+hi)/2;
		if(s[mid] - margin < val){
			lo = mid + 1;
		} else {
			hi = mid - 1;
		}
	}
	return lo;
}

int main(){
	scanf("%d", &N);
	for(int i=0;i<N;++i){
		scanf("%d", &a[i]);
		a[i]--;
		sum[i] = a[i];
		if(i>0) sum[i] += sum[i-1];
		_sum[i] = i + 1 - sum[i];
	}
	for(int k=1;k<=N;++k){
		bool ok = true;
		int score[2] = {0,0};
		int acc[2] = {0,0};
		int last_win = -1;
		while(1){
			int pos = bsearch(sum, k, acc[0]);
			if(pos >= N || sum[pos]-acc[0] != k || sum[pos] - acc[0] <= _sum[pos] - acc[1]) {
				pos = bsearch(_sum, k, acc[1]);
				if(pos >= N || _sum[pos]-acc[1] != k) {
					ok = false;
					break;
				} else {
					++score[1];
					last_win = 1;
				}
			} else {
				score[0] ++;
				last_win = 0;
			}
			acc[0] = sum[pos];
			acc[1] = _sum[pos];
			if(pos == N-1) break;
		}
		if(!ok || score[0] == score[1]) continue;
		if((score[0] > score[1] && last_win == 0) ||
		   (score[0] < score[1] && last_win == 1) ){
			st.push_back(make_pair(max(score[0], score[1]), k));
		}
	}
	sort(st.begin(), st.end());
	printf("%d\n", (int)st.size());
	for(int i=0;i<st.size();++i){
		printf("%d %d\n", st[i].first, st[i].second);
	}
	return 0;
}