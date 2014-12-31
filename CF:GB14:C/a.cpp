#include <iostream>
#include <cstdio>
#include <algorithm>
#include <deque>
using namespace std;

deque<int> st;
int w[503];
int N, M;
int main(){
	scanf("%d %d", &N, &M);
	for(int i=1;i<=N;++i){
		scanf("%d", &w[i]);
	}
	int b;
	int ans = 0;
	for(int i=0;i<M;++i){
		scanf("%d", &b);
		bool found = false;
		int val = 0;
		for(int j=0;j<st.size();++j){
			if(b == st[j]){
				found = true;
				st.erase(st.begin() + j);
				break;
			}
			val += w[st[j]];
		}
		ans += val;
		st.push_front(b);
	}
	printf("%d\n", ans);
	return 0;
}