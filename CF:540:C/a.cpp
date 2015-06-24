#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <utility>
using namespace std;
int n, m;
char b[510][510];
struct {
	int x;
	int y;
} src, tgt;
int vis[510][510];
pair<int,int> par[510][510];

int cnt(int i, int j) {
	if (i <= 0 || j <= 0 || i > n || j > m) return 0;
	return (b[i][j] == '.' ? 1 : 0);
}

int getcount() {
	return cnt(tgt.x-1, tgt.y) + cnt(tgt.x, tgt.y-1)
				+ cnt(tgt.x+1, tgt.y) + cnt(tgt.x, tgt.y+1);
}

bool cannot() {
	if (b[tgt.x][tgt.y] == 'X') return false; 
	return (getcount() == 0);
}


void enq(queue<pair<int,int> > &q, int i, int j, int x, int y) {
	if(vis[i][j]) return;
	if(b[i][j] == 'X' && (i != tgt.x || j != tgt.y)) return;
	if(i <= 0 || j <= 0 || i > n || j > m) return;
	vis[i][j] = 1;
	par[i][j] = make_pair(x,y);
	q.push(make_pair(i,j));
}

void bfs() {
	queue<pair<int,int> > q;
	q.push(make_pair(src.x, src.y));
	vis[src.x][src.y] = 1;
	bool ok = false;
	while (!q.empty()){
		int x = q.front().first;
		int y = q.front().second;
		if(tgt.x == x && tgt.y == y) {
			ok = true;
			break;
		}
		q.pop();
		enq(q, x-1, y, x, y);
		enq(q, x, y-1, x, y);
		enq(q, x+1, y, x, y);
		enq(q, x, y+1, x, y);
	}
	if (!ok) {
		printf("NO\n");
		return;
	}
	int x = par[tgt.x][tgt.y].first;
	int y = par[tgt.x][tgt.y].second;
	b[x][y] = 'X';
	if(cannot()) printf("NO\n");
	else printf("YES\n");
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			scanf(" %c",&b[i][j]);
		}
	}
	scanf("%d%d",&src.x, &src.y);
	scanf("%d%d",&tgt.x, &tgt.y);
	if(tgt.x == src.x && tgt.y == src.y) {
		if(b[tgt.x][tgt.y] == 'X') {
			if (getcount() == 0) {
				printf("NO\n");
			} else {
				printf("YES\n");
			}
		} else {
			if (getcount() < 2) {
				printf("NO\n");
			} else {
				printf("YES\n");
			}
		}
		return 0;
	}
	bfs();
	return 0;
}