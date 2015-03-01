#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
using namespace std;

vector<int> t[30];
string s;
long long sum[100005];
int val[30];
int N;
int main(){
	for(int i=0;i<26;++i){
		scanf("%d",&val[i]);
	}
	cin >> s;
	N = s.size();
	sum[0] = 0;
	for(int i=0;i<N;++i){
		sum[i+1] = sum[i] + val[s[i]-'a'];
		t[s[i]-'a'].push_back(i+1);
	}
	long long ans = 0;
	for(int k=0;k<26;++k){
		long long tot = 0;
		map<long long,int> tmp;
		for(int i=0;i<t[k].size();++i){
			if(tmp.count(sum[t[k][i]-1])) {
				tot += tmp[sum[t[k][i]-1]];
			}
			if(tmp.count(sum[t[k][i]])) {
				tmp[sum[t[k][i]]]++;
			} else {
				tmp[sum[t[k][i]]] = 1;
			}
		}
		ans += tot;
	}
	cout << ans << endl;
	return 0;
}