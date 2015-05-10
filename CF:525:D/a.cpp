#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;

/**
 	Learning Lesson: In times where you can't see the big picture, go to the basics.

 	Observation: In 2x2 squares, if exists only one asterisk, change it to dot.
*/

int N, M;
string b[2003];
int ans;

bool check(int i, int j){
	if(i==N-1 || j==M-1 || i < 0 || j < 0) return false;
	int cnt = 0;
	for(int k=0;k<2;++k){
		cnt += (b[i][j+k] == '*' ? 1 : 0);
		cnt += (b[i+1][j+k] == '*' ? 1 : 0);
	}
	return cnt==1;
}

void clear(int i, int j){
	for(int k=0;k<2;++k){
		b[i][j+k] = '.';
		b[i+1][j+k] = '.';
	}
}

void checkandadd(queue<pair<int,int> > &q, int i, int j){
	if(i==N-1 || j==M-1 || i < 0 || j < 0) return;
	q.push(make_pair(i,j));
}

void bfs(int i, int j){
	queue<pair<int,int> > q;
	q.push(make_pair(i,j));
	while(!q.empty()){
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		bool ok = false;
		if(check(x,y)) clear(x,y), ok = true;
		if(!ok)continue;
		for(int m=-1;m<=1;++m){
			for(int n=-1;n<=1;++n){
				q.push(make_pair(x+m,y+n));
			}
		}
	}
}

int main(){
	scanf("%d%d",&N,&M);
	for(int i=0;i<N;++i){
		cin >> b[i];
	}
	ans = 0;
	for(int i=0;i<N-1;++i){
		for(int j=0;j<M-1;++j){
			if(check(i,j)) bfs(i,j);
		}
	}
	for(int i=0;i<N;++i){
		cout << b[i] << endl;
	}
	return 0;
}