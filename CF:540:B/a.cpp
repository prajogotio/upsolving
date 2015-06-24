#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

int n, k, p, x, y;
int main(){
	scanf("%d%d%d%d%d",&n,&k,&p,&x,&y);
	int v;
	int lo, hi;
	lo =  hi = 0;
	int sum = 0;
	for(int i=0;i<k;++i){
		scanf("%d",&v);
		sum += v;
		if(v < y) lo++;
		else hi++;
	}
	int rem = x - sum;
	if (rem < n-k) {
		printf("-1\n");
		return 0;
	}
	vector<int> st;
	for(int i=0;i<n-k;++i){
		if(rem - y >= n-k-i-1) {
			st.push_back(y);
			++hi;
			rem -= y;
		}else {
			st.push_back(1);
			++lo;
			rem -= 1;
		}
	}
	if(hi > lo) {
		for(int i = 0; i < n-k; ++i){
			printf("%d ", st[i]);
		}
		printf("\n");
	} else {
		printf("-1\n");
	}
	return 0;
}