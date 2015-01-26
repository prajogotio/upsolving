#include <iostream>
#include <cstdio>
#include <queue>
#include <utility>
using namespace std;

int linklist[500003][2];
int a[500003];
int mark[500003];
priority_queue<pair<int,int> > pq;
int N;
int main(){
	scanf("%d",&N);
	for(int i=0;i<N;++i){
		scanf("%d",&a[i]);
	}
	for(int i=0;i<N;++i){
		if(i > 0) {
			linklist[i][0] = i-1;
		} else {
			linklist[i][0] = -1;
		}
		if(i+1 < N) {
			linklist[i][1] = i+1;
		} else {
			linklist[i][1] = -1;
		}
	}
	for(int i=1;i<N-1;++i){
		if(a[i-1] >= a[i] && a[i] <= a[i+1]) {
			pq.push(make_pair(-a[i], i));
			mark[i] = 1;
		}
	}
	long long ans = 0;
	while(!pq.empty()) {
		int i = pq.top().second;
		pq.pop();
		ans += min(a[linklist[i][0]], a[linklist[i][1]]);
		int left = linklist[i][0];
		int right = linklist[i][1];
		if(left != -1) linklist[left][1] = right;
		if(right != -1) linklist[right][0] = left;
		if(left != 0 && linklist[left][0] != -1 && linklist[left][1] != -1){
			if(a[linklist[left][0]] >= a[left] && a[left] <= a[linklist[left][1]]) {
				if(!mark[left]){
					mark[left] = 1;
					pq.push(make_pair(-a[left], left));
				}
			}
		}
		if(right != N-1 && linklist[right][0] != -1 && linklist[right][1] != -1) {
			if(a[linklist[right][0]] >= a[right] && a[right] <= a[linklist[right][1]]) {
				if(!mark[right]){
					mark[right] = 1;
					pq.push(make_pair(-a[right], right));
				}
			}
		}
	}
	int cur = linklist[0][1];
	while(cur != -1 && cur != N-1) {
		ans += min(a[linklist[cur][0]], a[linklist[cur][1]]);
		cur = linklist[cur][1];
	}
	cout << ans << endl;
	return 0;
}