#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

/* MEMORY LIMIT EXCEEDED*/

string s;
long long MOD = (long long) 1e9 + 7LL;
int $ = -1;
int r[20][5005];
long long dp[5005][5005];
vector<pair<int,int> > edge[5005][5005];
int n;
int minlenleaf, minlendepth;

//is [i..j] <= [j+1 .. (2*j+i-1)] ?
int check(int len, int i, int j){
	int k = -1;
	int tmp = len;
	while(tmp){
		++k;
		tmp >>= 1;
	}
	int L = 1 << k;
	if(L == len) {
		return r[k][i] <= r[k][j+1];
	}
	if(r[k][i] == r[k][j+1]){
		int offset = len - L;
		return r[k][i+offset] <= r[k][j+1+offset];
	}
	return r[k][i] < r[k][j+1];
}

void dfs(pair<int,int> node, int depth){
	bool isleaf = true;
	for(int i=0;i<edge[node.first][node.second].size();++i){
		pair<int,int> v = edge[node.first][node.second][i];
		isleaf = false;
		dfs(v, depth+(v.first == node.first ? 0 : 1));
	}
	if(isleaf){
		if(s[node.first] == '0') return;
		if(minlenleaf == -1){
			minlenleaf = node.first;
			minlendepth = depth;
		} else {
			if(node.first  == minlenleaf){
				minlendepth = min(minlendepth, node.second);
			} else if(node.first > minlenleaf){
				int len = n - node.first;
				int curlen = n - minlenleaf;
				if(curlen >= 13) {
					minlenleaf = node.first;
					minlendepth = depth;
				} else {
					int curval = 0, val = 0;
					for(int i=node.first;i<n;++i){
						val *= 2;
						val += (s[i] == '1' ? 1 : 0);
					}
					for(int i=minlenleaf;i<n;++i){
						curval *= 2;
						val += (s[i] == '1' ? 1 : 0);
					}
					if(curval + depth < val){
						minlenleaf = node.first;
						minlendepth = depth;
					}
				}
			}
		}
	}
}

int main(){
	cin >> s;
	n = s.size();
	for(int i=0;i<n;++i) r[0][i] = (int)s[i];
	for(int k=1,len=1;;++k,len*=2){
		vector<pair<pair<int,int>,int> > st;
		for(int i=0;i<n;++i){
			int j = i+len;
			if(j >= n) j = $;
			else j = r[k-1][j];
			st.push_back(make_pair(make_pair(r[k-1][i],j),i));
		}
		sort(st.begin(), st.end());
		int cnt = 0;
		r[k][st[0].second] = cnt;
		for(int i=1;i<n;++i){
			if(st[i].first != st[i-1].first) ++cnt;
			r[k][st[i].second] = cnt;
		}
		if(len >= n) {
			break;
		}
	}
	/*
	for(int k=0;k<=sz;++k){
		for(int i=0;i<n;++i) printf("%d ", r[k][i]);printf("\n");
		vector<pair<int,int> > test;
		for(int i=0;i<n;++i) test.push_back(make_pair(r[k][i],i));
		sort(test.begin(), test.end());
		for(int i=0;i<n;++i) cout << s.substr(test[i].second, n-test[i].second) << endl;
	}
	*/
	for(int i=0;i<n;++i){
		dp[i][n-1] = (s[i] == '1' ? 1 : 0);
	}
	for(int j=n-2;j>=0;--j){
		for(int i=0;i<=j;++i){
			dp[i][j] = dp[i][j+1];
			edge[i][j].push_back(make_pair(i,j+1));
			if(s[j+1] != '0'){
				if(2*j-i+1 < n && check(j-i+1, i, j)){
					dp[i][j] = (dp[i][j] + dp[j+1][2*j-i+1]) % MOD;
					edge[i][j].push_back(make_pair(j+1,2*j-i+1));
				} else if (2*j-i+2 < n){
					dp[i][j] = (dp[i][j] + dp[j+1][2*j-i+2]) % MOD;
					edge[i][j].push_back(make_pair(j+1,2*j-i+2));
				}
			}
		}
	}
	minlenleaf = -1;
	dfs(make_pair(0,0), 0);
	long long minval = 0;
	for(int i=minlenleaf;i<n;++i){
		minval *= 2LL;
		minval += (s[i] == '1' ? 1 : 0);
		minval %= MOD;
	}
	minval += minlendepth;
	minval %= MOD;
	++minval;
	printf("%d\n", (int) dp[0][0]);
	printf("%d\n", (int) minval);
	return 0;
}