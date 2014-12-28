#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cstring>
using namespace std;

int INF = (int) 1e9;

class ChessMatchup {
public:
	int adj[102][102];
	int M, N;
	int l[102], S[102], T[102], Nq[102];
	int path[102], match[102];
	int root;
	int par[102];

	void computeNq(){
		memset(Nq, 0, sizeof Nq);
		for(int i=0;i<N;++i){
			if(!S[i])continue;
			for(int j=N;j<2*N;++j){
				if(l[i] + l[j] == adj[i][j]){
					Nq[j] = 1;
					if(match[j] != i) par[j] = i;
				}
			}
		}
	}

	bool TequalsNq(){
		for(int i=N;i<2*N;++i){
			if(T[i] != Nq[i]) return false;
		}
		return true;
	}

	void augment_path(int v, int state){
		int u = path[v];
		if(u == v) return;
		if(state){
			match[u] = v;
			match[v] = u;
		}
		augment_path(u, state^1);
	}

	int maximumScore(vector<int> us, vector<int> them){
		N = us.size();
		for(int i=0;i<N;++i) memset(adj[i], 0, sizeof adj[i]);
		memset(l, 0, sizeof l);
		for(int i=0;i<N;++i){
			for(int j=0;j<N;++j){
				int tmp = us[i] - them[j];
				if(tmp > 0) tmp = 2;
				else if(tmp == 0) tmp = 1;
				else tmp = 0;
				adj[i][j+N] = tmp;
				adj[j+N][i] = tmp;
			}
		}
		//for(int i=0;i<2*N;++i){for(int j=0;j<2*N;++j) printf("%d ", adj[i][j]); printf("\n");}
		//initialize labelling
		for(int i=0;i<N;++i){
			for(int j=0;j<N;++j){
				l[i] = max(l[i], adj[i][j+N]);
			}
		}
		M = 0;
		for(int i=0;i<2*N;++i) match[i] = i;
		while(M != N){
			memset(S, 0, sizeof S);
			memset(T, 0, sizeof T);
			for(int i=0;i<2*N;++i) path[i] = i;
			for(int i=0;i<N;++i){
				if(match[i] == i){
					S[i] = 1;
					root = i;
					break;
				}
			}
			while(true){
				computeNq();
				//printf("%d\n", M);
				//for(int i=0;i<2*N;++i)printf("%d ", l[i]);printf("\n");
				// for(int i=0;i<2*N;++i)printf("%d ", S[i]);printf("\n");
				// for(int i=0;i<2*N;++i)printf("%d ", T[i]);printf("\n");
				// for(int i=0;i<2*N;++i)printf("%d ", Nq[i]);printf("\n");
				// for(int i=0;i<2*N;++i)printf("%d ", par[i]);printf("\n");
				// for(int i=0;i<2*N;++i)printf("%d ", match[i]);printf("\n");
				// for(int i=0;i<2*N;++i)printf("%d ", path[i]);printf("\n");
				if(TequalsNq()){
					int alpha = 12345;
					for(int i=0;i<N;++i){
						if(!S[i])continue;
						for(int j=N;j<2*N;++j){
							if(T[j])continue;
							alpha = min(alpha, l[i] + l[j] - adj[i][j]);
						}
					}
					assert(alpha != INF && alpha != 0);
					for(int i=0;i<2*N;++i){
						if(S[i]) l[i] -= alpha;
						if(T[i]) l[i] += alpha;
					}
					computeNq();
				}
				int y = -1;
				for(int i=N;i<2*N;++i){
					if(Nq[i] && !T[i]) {
						y = i;
						break;
					}
				}
				assert(y >= 0);
				if(match[y] == y){
					path[y] = par[y];
					augment_path(y, 1);
					++M;
					break;
				} else {
					path[y] = par[y];
					path[match[y]] = y;
					S[match[y]] = 1;
					T[y] = 1;
				}
			}
		}
		int ans = 0;
		for(int i=0;i<2*N;++i){
			ans += l[i];
		}
		return ans;
	}
};

int main(){
	vector<int> us;
	vector<int> them;
	int a[] = {1,10,7,4};
	int b[] = {15,3,8,7};
	us.assign(a, a + (sizeof a)/(sizeof a[0]));
	them.assign(b, b + (sizeof b)/(sizeof b[0]));
	ChessMatchup test;
	cout << test.maximumScore(us, them) << endl;
}