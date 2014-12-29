#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
long long MOD = (long long) 1e9 + 7LL;
vector<vector<int> > adj;
int BLACK = 1, WHITE = 0;
int N;
int color[100005];
int vis[100005];
long long black[100005];	/* number of ways such that node u is a subtree with one black node */
long long white[100005];	/* number of ways such that node u is a subtree with no black node */
							/* for each cases, all the remaining subtrees below u must have
					   		one black node, so black[root] is the answer to the question */

void dfs(int u) {
	vis[u] = 1;
	long long w = 0;
	long long b = 0;
	black[u] = white[u] = 0;
	if(color[u] == BLACK) b = 1;
	else w = 1;

	for(int i=0;i<adj[u].size();++i){
		int v = adj[u][i];
		if(vis[v]) continue;
		dfs(v);
		if(color[u] == WHITE){
			if(color[v] == WHITE){
				// if i want subtree u to be one black,
				// i v must be one black and u current is all white
				// or u is currently one black, so v must be white.
				// or u is currently one black, and i just cut v.
				b = ((b * ((black[v] + white[v])%MOD)) % MOD) + ((w * black[v]) % MOD);
				b %= MOD;
				// if i want subtree u to be all white,
				// i can choose to include v all white,
				// or not to include v, children of v must be one black.
				w *= ((white[v] + black[v])%MOD);
				w %= MOD;
			} else {
				// unless, i want one black
				// hence if u is currently one black, cut v
				// otherwise, u is currently white, add v.
				b = ((b * black[v]) % MOD) + ((w * black[v]) % MOD);
				b %= MOD;

				// if i want u to be all white, i must cut v
				w *= (black[v]);
				w %= MOD;
			}
		} else {
			// u is currently black
			// i can only have u to be one black
			if(color[v] == WHITE){
				// v is white, so safe to add v
				// or cut v
				b *= ((white[v] + black[v]) % MOD);
				b %= MOD;
			} else {
				// v is black, i can only cut v
				b *= black[v];
				b %= MOD;
			}
		}
	}
	black[u] = b;
	white[u] = w;
}

int main(){
	int u;
	scanf("%d", &N);
	adj = vector<vector<int> >(N+3);
	for(int i=0;i<N-1;++i){
		scanf("%d", &u);
		adj[i+1].push_back(u);
		adj[u].push_back(i+1);
	}
	for(int i=0;i<N;++i){
		scanf("%d", &color[i]);
	}
	dfs(0);
	cout << black[0] << endl;
	return 0;
}