#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

multiset<int> s;
vector<int> p[200010];
int n;
int main(){
	scanf("%d",&n);
	int u;
	for(int i=1;i<=n;++i){
		scanf("%d",&u);
		s.insert(u);
		p[u].push_back(i);
	}
	vector<int> ans;
	bool ok = true;
	int cnt = 0;
	for(int i=0;i<n;++i){
		while(cnt-3 >= 0 && s.find(cnt) == s.end()) cnt -= 3;
		if(s.find(cnt) == s.end()) {
			ok = false;
			break;
		}
		s.erase(s.find(cnt));
		ans.push_back(p[cnt].back());
		p[cnt].pop_back();
		++cnt;
	}
	if(ok){
		printf("Possible\n");
		for(int i=0;i<n;++i)printf("%d ",ans[i]);printf("\n");
	} else {
		printf("Impossible\n");
	}
	return 0;
}