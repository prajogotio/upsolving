#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

/*
   Lesson: blunt tools can be more powerful than sharpest swords!
   Observation: 
   After adding minimum number of edges, the resulting graph:
   1. all the vertices have even degree
   2. exist an euler path traversing through all edges
   3. the euler path must have even length: 
      so that we can have v1 -> v2 -> v3 -> ... -> vn -> v1,
      since there are even length, if we flip alternate the arrow,
      we will get v1 -> v2 <- v3 -> ... -> vn <- v1
      which satisfy the constraint!
   4. if by construct we get an euler path with odd length, just add a self loop!

   Euler Path: use multiset to support deletion in lg E time, processing each edge only once
   pessimistic O(E lg E)
*/


int N, M;
int deg[200003];
vector<int> st;
vector<int> euler;
multiset<int> adj[200003];

void findeuler(int u){
	while(!adj[u].empty()){
		int v = *(adj[u].begin());
		adj[u].erase(adj[u].begin());
		adj[v].erase(adj[v].find(u));
		findeuler(v);
	}
	euler.push_back(u);
}

int main(){
	scanf("%d%d",&N,&M);
	int u,v;
	for(int i=0;i<M;++i){
		scanf("%d%d",&u,&v);
		deg[u]++;
		deg[v]++;
		adj[u].insert(v);
		adj[v].insert(u);
	}
	int odd = 0;
	for(int i=1;i<=N;++i){
		if(deg[i]%2) st.push_back(i);
		odd += deg[i]%2;
	}
	for(int i=0;i<st.size();i+=2){
		++M;
		adj[st[i]].insert(st[i+1]);
		adj[st[i+1]].insert(st[i]);
	}
	if(M%2){
		M += M%2;
		adj[1].insert(1);
		adj[1].insert(1);
	}
	findeuler(1);
	printf("%d\n",M);
	for(int i=0;i+1<euler.size();++i){
		if(i%2){
			printf("%d %d\n",euler[i], euler[i+1]);
		}
		else {
			printf("%d %d\n",euler[i+1], euler[i]);
		}
	}
	return 0;
}
