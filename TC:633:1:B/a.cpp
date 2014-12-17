#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

int INF = 1234567;
int S = 55;
int T = 56;
vector<vector<int> > adj[2];
vector<vector<int> > G;
int cap[60][60];
int flow[60][60];
int par[60];
int vis[2][60];
int N;

void clear_state(int N) {
	for(int i=0;i<N+3;++i){
		for(int j=0;j<N+3;++j){
			cap[i][j] = flow[i][j] = 0;
		}
	}
	for(int i=0;i<2;++i){
		for(int j=0;j<N;++j){
			vis[i][j] = 0;
		}
	}
	G = vector<vector<int> > (N+3);
}

void dfs(int t, int u) {
	vis[t][u] = 1;
	for(int i=0;i<adj[t][u].size();++i){
		int v = adj[t][u][i];
		if(vis[t][v]) continue;
		dfs(t, v);
		cap[v][u] = INF;
		G[u].push_back(v);
		G[v].push_back(u);
	}
}

void init(vector<int>& score) {
	for(int i=0;i<N;++i) {
		if(score[i] > 0) {
			cap[S][i] = score[i];
			G[S].push_back(i);
			G[i].push_back(S);
		} else {
			cap[i][T] = -score[i];
			G[T].push_back(i);
			G[i].push_back(T);
		}
	}
}


int maxflow;

int augment_path(int v, int f) {
	if(v == S) {
		//printf("%d ", v);
		return f;
	}
	int u = par[v];
	int backedge = 0;
	int mf = 0;
	if(cap[u][v] > 0) {
		backedge = 0;
		mf = cap[u][v] - flow[u][v];
	} else {
		backedge = 1;
		mf = flow[v][u];
	}
	int minf = augment_path(u, min(mf, f));
	//printf("%d ", v);
	if(!backedge) {
		flow[u][v] += minf;
	} else {
		flow[v][u] -= minf;
	}
	return minf;
}

void edmondskarp() {
	maxflow = 0;
	while(1) {
		for(int i=0;i<60;++i) par[i] = -1;
		queue<int> q;
		q.push(S);
		par[S] = S;
		bool found = false;
		while(!q.empty()) {
			int u = q.front();
			q.pop();
			for(int i=0;i<G[u].size(); ++i){
				int v = G[u][i];
				if(par[v] != -1) continue;
				if(cap[u][v] - flow[u][v] > 0 || flow[v][u] > 0) {
					par[v] = u;
					if(v == T) {
						found = true;
						break;
					} else {
						q.push(v);
					}
				}
			}
			if(found) break;
		}
		if(found) {
			maxflow += augment_path(T, INF);
			/*
			printf("\n");
			printf("maxflow: %d\n", maxflow);
			for(int i=0;i<N+3;++i){
				for(int j=0;j<N+3;++j){
					printf("(%d,%d) ", cap[i][j], flow[i][j]);
				}
				printf("\n");
			}
			*/
		} else {
			break;
		}
	}
}

class DoubleTree {
public:
	int maximalScore(vector<int> a, vector<int> b, vector<int> c, vector<int> d, vector<int> score) {
		//SPECIAL CASE: when all scores are positive, just return the whole tree
		N = score.size();
		S = N+1;
		T = N+2;
		for(int i=0;i<2;++i){
			adj[i] = vector<vector<int> >(N+3);
		}
		for(int i=0;i<N-1;++i) {
			adj[0][a[i]].push_back(b[i]);
			adj[0][b[i]].push_back(a[i]);
		}
		for(int i=0;i<N-1;++i){
			adj[1][c[i]].push_back(d[i]);
			adj[1][d[i]].push_back(c[i]);
		}
		int sum = 0;
		bool special_case = true;
		for(int i=0;i<N;++i){
			if(score[i] > 0) sum += score[i];
			else special_case = false;
		}
		if(special_case || sum == 0) {
			return sum;
		} else {
			int ans = 0;
			for(int i=0;i<N;++i) {
				clear_state(N);
				dfs(0,i);
				dfs(1,i);
				init(score);
				edmondskarp(); 
				int tmp = sum - maxflow;
				ans = max(ans, tmp);
			}
			return ans;
		}
	}
};


int main(){
	/*
	int a[] = {0,0,1};
	int b[] = {1,3,2};
	int c[] = {0,0,3};
	int d[] = {1,3,2};
	int s[] = {1000,24,100,-200};
	*/
	/*
	int a[] = {0,0,1};
int b[] = {1,3,2};
int c[] = {0,0,3};
int d[] = {1,3,2};
int s[] = {-1000,24,100,200};
*/

int a[] = {0,0,1,1,2,2};
int b[] = {1,2,3,4,5,6};
int c[] ={0,0,1,1,2,2};
int d[] ={1,2,3,4,5,6};
int s[] ={-3,2,2,-1,2,2,-1};
	vector<int> A,B,C,D,S;
	A.assign(a, a + (sizeof a / sizeof a[0]));
	B.assign(b, b + (sizeof b / sizeof b[0]));
	C.assign(c, c + (sizeof c / sizeof c[0]));
	D.assign(d, d + (sizeof d / sizeof d[0]));
	S.assign(s, s + (sizeof s / sizeof s[0]));
	DoubleTree test;
	cout << test.maximalScore(A, B, C, D, S) << endl;
	return 0;

}