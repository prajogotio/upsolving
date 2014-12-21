#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;


//wrong approach
// cant think of an efficient way to find [L, R] in {(Li, Ri)} that contains [A,B] just nicely.


vector<pair<int,int> > jobs;
vector<pair<int,int> > person;
vector<int> val;
vector<vector<int> > adj;
int n, m;
int u, v, w;
int mark[100005];
int par[100005];
int jrank[100005];
int prank[100005];
bool ok = true;

bool fn1(const int& L, const int& R){
	return jobs[L].second - jobs[L].first < jobs[R].second - jobs[R].first;
}

bool fn2(const int& L, const int& R){
	if(person[L].first == person[R].first){
		if(person[L].second == person[R].second){
			return val[L] > val[R];
		}
		return person[L].second > person[R].second;
	}
	return person[L] < person[R];
}

int bsearch(int u){
	int lo = 0, hi = m-1, mid;
	while(lo <= hi){
		mid = (lo+hi)/2;

	}
}

int main(){
	scanf("%d", &n);
	for(int i=0;i<n;++i){
		jrank[i] = i;
		scanf("%d%d", &u,&v);
		jobs.push_back(make_pair(u,v));
	}
	for(int i=0;i<m;++i){
		prank[i] = i;
		scanf("%d%d%d", &u,&v,&w);
		person.push_back(make_pair(u,v));
		val.push_back(w);
	}
	adj = vector<vector<int> > (m+3);
	vector<int> st;
	for(int i=0;i<m;){
		if(st.empty()){
			st.push_back(i);
			++i;
		} else if((person[st.back()].first <= person[i].first &&
			              person[i].second <= person[st.back()].second) ){
			adj[i].push_back(st.back());
			st.push_back(i);
			++i;
		} else {
			st.pop_back();
		}
	}

	return 0;
}