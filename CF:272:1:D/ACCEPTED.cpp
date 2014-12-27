#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;


string s;
long long MOD = (long long) 1e9 + 7LL;
int $ = -1;
int r[20][5005];
long long dp[5005][5005];
int cmp[5005];
pair<int,int> val[5005][5005];
int n;

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

void update_path(int i, int j, int u, int v){
	if(val[i][j].first == -1){
		val[i][j] = val[u][v];
		if(i!=u) val[i][j].second ++;
	} else {
		if(val[i][j].first == val[u][v].first){
			val[i][j].second = min(val[i][j].second, val[u][v].second + (i != u ? 1 : 0));
		} else if(val[i][j].first < val[u][v].first) {
			if(n - val[i][j].first >= 13) {
				val[i][j] = val[u][v];
				if(i != u) val[i][j].second++;
			} else {
				int tmp = cmp[val[u][v].first] + val[u][v].second + (u!=i?1:0);
				if(cmp[val[i][j].first] + val[i][j].second > tmp){
					val[i][j] = val[u][v];
					if(u!=i)val[i][j].second ++;
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
	for(int i=max(0,n-13);i<n;++i){
		cmp[i] = 0;
		for(int j=i;j<n;++j){
			cmp[i] *= 2;
			cmp[i] += (s[j] == '1' ? 1 : 0);
		}
	}
	for(int i=0;i<n;++i)
		for(int j=0;j<n;++j)
			val[i][j].first = -1;
	for(int i=0;i<n;++i){
		dp[i][n-1] = (s[i] == '1' ? 1 : 0);
		val[i][n-1] = make_pair(i,1);
	}
	for(int j=n-2;j>=0;--j){
		for(int i=0;i<=j;++i){
			dp[i][j] = dp[i][j+1];
			update_path(i,j,i,j+1);
			if(s[j+1] != '0'){
				if(2*j-i+1 < n && check(j-i+1, i, j)){
					dp[i][j] = (dp[i][j] + dp[j+1][2*j-i+1]) % MOD;
					update_path(i,j,j+1,2*j-i+1);
				} else if (2*j-i+2 < n){
					dp[i][j] = (dp[i][j] + dp[j+1][2*j-i+2]) % MOD;
					update_path(i,j,j+1,2*j-i+2);
				}
			}
		}
	}
	long long minlen = 0;
	for(int i = val[0][0].first; i < n;++i){
		minlen *= 2LL;
		minlen %= MOD;
		minlen += (s[i] == '1'? 1:0);
		minlen %= MOD;
	}
	minlen += val[0][0].second;
	minlen %= MOD;
	printf("%d\n", (int) dp[0][0]);
	printf("%d\n", (int) minlen);
	return 0;
}