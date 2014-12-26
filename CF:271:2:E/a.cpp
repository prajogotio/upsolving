#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <utility>
#include <map>
using namespace std;

//wrong approach

int n, d;
map<long long, int> s;
typedef map<long long, int>::iterator sit;
int val[100005];
int par[100005];

void printout(int u){
	if(par[u] == -1){
		printf("%d", u);
		return;
	}
	printout(par[u]);
	printf(" %d", u);
}

int main(){
	scanf("%d%d", &n, &d);
	long long u;
	int ans = -1;
	int maxans = 0;
	for(int i=1;i<=n;++i){
		cin >> u;
		if(i==1){
			val[1] = 1;
			par[1] = -1;
		} else {
			val[i] = 1;
			par[i] = -1;
			sit k = s.upper_bound(make_pair(u-d,i));
			if(k != s.begin()) {
				--k;
				if(val[k->second] + 1 > val[i]) {
					val[i] = val[k->second] + 1;
					par[i] = k->second;
				}
			}
			k = s.upper_bound(make_pair(u+d, i));
			if(k != s.begin()) {
				if(k->first >= u+d && val[k->second] + 1 > val[i]) {
					val[i] = val[k->second] + 1;
					par[i] = k->second;
				}
				--k;
				if(k->first >= u+d && val[k->second] + 1 > val[i]) {
					val[i] = val[k->second] + 1;
					par[i] = k->second;
				}
			}
		}
		if(maxans < val[i]) {
			maxans = val[i];
			ans = i;
		}
		s.insert(make_pair(u, i));
	}
	printf("%d\n", maxans);
	printout(ans);
	printf("\n");
}