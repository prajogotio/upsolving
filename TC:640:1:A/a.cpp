#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int par[100];
int mark[203];
void init_dsu() {
	for(int i=0;i<100;++i) par[i] = i;
}

int find_par(int i) {
	return (par[i] == i ? i : (par[i] = find_par(par[i])));
}

void merge(int i, int j){
	int x = find_par(i);
	int y = find_par(j);
	par[x] = y;
}

class ChristmasTreeDecoration {
public:
	int solve(vector<int> col, vector<int> x, vector<int> y) {
		init_dsu();
		int N = col.size();
		int M = x.size();
		int chosen = 0;
		for(int i=0;i<M;++i){
			mark[i] = 0;
		}
		for(int i=0;i<N-1;++i){
			bool found = false;
			for(int i=0;i<M;++i){
				if(found) break;
				if(mark[i]) continue;
				if(col[x[i]-1] == col[y[i]-1]) continue;
				if(find_par(x[i]-1) == find_par(y[i]-1)) continue;
				mark[i] = 1;
				merge(x[i]-1, y[i]-1);
				++chosen;
				found = true;
			}
			if(!found) break;
		}
		return N-1 - chosen;
	}
};