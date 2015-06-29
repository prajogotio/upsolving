#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

/* memory limit exceeded */

long long dp[510][510][510];
int n, m, b;
long long mod;
int a[510];
int vis[510][510][510];
struct node {
	int i, t, b;
	node(int x, int y, int z):i(x), t(y), b(z){}
};

void enq(queue<node> &q, node &cur, int ni, int nt, int nb) {
	if(ni > n || nt < 0 || nb > b) return;
	dp[ni][nt][nb] += dp[cur.i][cur.t][cur.b];
	dp[ni][nt][nb] %= mod;
	if(vis[ni][nt][nb]) return;
	vis[ni][nt][nb] = 1;
	q.push(node(ni, nt, nb));
}

int main(){
	cin >> n >> m >> b >> mod;
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	dp[1][m][0] = 1;
	queue<node> q;
	q.push(node(1, m, 0));
	vis[1][m][0] = 1;
	while(!q.empty()){
		node cur = q.front();
		q.pop();
		enq(q, cur, cur.i+1, cur.t, cur.b);
		enq(q, cur, cur.i, cur.t - 1, cur.b + a[cur.i]);
	}
	long long ans = 0;
	for(int i=0;i<=b;++i){
		ans += dp[n][0][i];
		ans %= mod;
	}
	cout << ans << endl;
	return 0;
}