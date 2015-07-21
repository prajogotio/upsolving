#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
int n;
int a[200010], lo[200010], hi[200010], maxval[200010];

/*
	how would one find largest j such that j < i and a[j] < a[i]
	in O(N)? use monotonic queue
	how would one find largest val in [i...n] from i = 1 to n?
	monotonic queue
*/
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;++i)scanf("%d",&a[i]);
	vector<int> mono;
	for(int i=0;i<n;++i){
		while(!mono.empty() && a[mono.back()]>=a[i]){
			mono.pop_back();
		}
		if(mono.empty()){
			lo[i] = -1;
		} else {
			lo[i] = mono.back();
		}
		mono.push_back(i);
	}
	mono.clear();
	for(int i=n-1;i>=0;--i){
		while(!mono.empty() && a[mono.back()]>=a[i]){
			mono.pop_back();
		}
		if(mono.empty()){
			hi[i] = n;
		} else {
			hi[i] = mono.back();
		}
		mono.push_back(i);
	}
	for(int i=0;i<n;++i){
		int len = hi[i]-lo[i]-1;
		maxval[len] = max(maxval[len], a[i]);
	}
	mono.clear();
	for(int i=1;i<=n;++i){
		while(!mono.empty() && maxval[mono.back()]<=maxval[i]){
			mono.pop_back();
		}
		mono.push_back(i);
	}
	int j = 0;
	for(int i=1;i<=n;++i){
		while(mono[j]<i)++j;
		printf("%d ", maxval[mono[j]]);
	}
	printf("\n");
	return 0;
}