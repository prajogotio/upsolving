#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
#include <cstring>
using namespace std;


string s;
int INF = 1e9;
long long MOD = (long long) 1e9 + 7LL;
int $ = -1;
int N;
int r[5005];			// rank of prefix i
int a[5005]; 			// suffix array
int rmq[5005][5005]; 	// rmq[i][j] = index bigger and closest to i.
long long dp[5005][5005];
//O(nlg^2n) suffix array
void suffix_array(){
	vector<pair<int,int> > st;

	for(int i=0;i<N;++i){
		st.push_back(make_pair(s[i],i));
	}
	sort(st.begin(), st.end());
	int cnt = 0;
	r[st[0].second] = 0;
	for(int i=1;i<N;++i){
		if(st[i].first != st[i-1].first) ++cnt;
		r[st[i].second] = cnt;
	}

	for(int k=1;;k*=2){
		vector<pair<pair<int,int>,int> > rt;
		for(int i=0;i<N;++i){
			int j = $;
			if(i+k < N){
				j = r[i+k];
			}
			rt.push_back(make_pair(make_pair(r[i],j),i));
		}
		sort(rt.begin(), rt.end());
		cnt = 0;
		r[rt[0].second] = 0;
		for(int i=1;i<N;++i){
			if(rt[i].first != rt[i-1].first) ++cnt;
			r[rt[i].second] = cnt;
		}
		if(k>=N)break;
	}
	st.clear();
	for(int i=0;i<N;++i){
		st.push_back(make_pair(r[i],i));
	}
	sort(st.begin(),st.end());
	for(int i=0;i<N;++i){
		a[i] = st[i].second;
	}
	printf("rank:\n");
	for(int i=0;i<N;++i){
		printf("%d: %d\n", i, r[i]);
	}
	printf("\n");
	for(int i=0;i<N;++i){
		cout << a[i] << ": " <<  s.substr(a[i], N-a[i]) << endl;
	}
}

void build_rmq(){
	int mark[5005];
	for(int i=0;i<N;++i){
		for(int j=i;j<N;++j){
			if(s[j+1] == '0') {
				rmq[i][j] = INF;
				continue;
			}
			// is substring [j+1 .. 2j-i+1] > [i .. j] ?
			if(2*j-i+1 >= N) rmq[i][j] = INF;
			else if(r[i] < r[j+1]) {
				
				rmq[i][j] = 2*j-i+1;
			}
			else rmq[i][j] = 2*j-i;
		}
	}
	for(int i=0;i<N;++i){for(int j=0;j<N;++j)printf("%d ", rmq[i][j]); printf("\n");}
}

void solve(){
	for(int i=0;i<N;++i){
		dp[i][N-1] = (s[i] == '1' ? 1 : 0);
	}
	for(int j=N-2;j>=0;--j){
		for(int i=0;i<=j;++i){
			dp[i][j] = dp[i][j+1];
			if(rmq[i][j] != INF) dp[i][j] = (dp[i][j] + dp[j+1][rmq[i][j]]) % MOD;
		}
	}
	for(int i=0;i<N;++i){
		for(int j=0;j<N;++j){
			printf("%d ", (int)dp[i][j]);
		}
		printf("\n");
	}
	printf("%d\n", (int) dp[0][0]);
}

int main(){
	cin >> s;
	cout << s << endl;
	N = s.size();
	printf("\nsuffix array:\n");
	suffix_array();
	printf("\nrmq:\n");
	build_rmq();
	printf("\ndp:\n");
	solve();
	return 0;
}