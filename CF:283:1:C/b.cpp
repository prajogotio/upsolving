#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
int INF = (int) 1e9;
set<pair<int,int> > s;
int val[200005];
int mark[200005];
vector<pair<pair<int,int>,int> > v;
typedef set<pair<int,int> >::iterator sit;
int a,b,c;
int n,m;

void printsetout(){
	sit k = s.begin();
	while(k != s.end()){
		printf("%d %d\n", k->first, k->second);
		++k;
	}
}

bool fn(const pair<pair<int,int>,int>& L, const pair<pair<int,int>,int>& R){
	if((L.second < n && R.second < n) ||
		(L.second >= n && R.second >= n)) {
			return L.first < R.first;
	} else {
		if(L.first.first == R.first.first){
			return L.second > R.second;
		}
		return L.first < R.first;
	}

}

int main(){
	scanf("%d", &n);
	for(int i=0;i<n;++i){
		scanf("%d%d", &a, &b);
		v.push_back(make_pair(make_pair(a,b),i));
	}
	scanf("%d", &m);
	for(int i=n;i<n+m;++i){
		scanf("%d%d%d", &a,&b,&c);
		v.push_back(make_pair(make_pair(a,b),i));
		val[i] = c;
	}
	sort(v.begin(), v.end(), fn);

	for(int i=0;i<m+n;++i){
		/*
		printf("==>%d\n###\n", i);
		printsetout();
		printf("###\n");
		printf("%d %d %d\n", v[i].first.first, v[i].first.second, v[i].second);
		*/
		if(v[i].second >= n) s.insert(make_pair(v[i].first.second, v[i].second));
		else {
			sit k = s.lower_bound(make_pair(v[i].first.second, 0));
			if(k == s.end()) {
				printf("NO\n");
				return 0;
			}
			mark[v[i].second] = k->second;
			val[k->second] --;
			if(val[k->second] == 0) s.erase(k);
		}
	}
	printf("YES\n");
	for(int i=0;i<n;++i){
		if(i!=0)printf(" ");
		printf("%d", mark[i]-n+1);
	}
	printf("\n");
	return 0;
}