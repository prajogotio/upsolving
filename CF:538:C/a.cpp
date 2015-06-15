#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

namespace mine{

int n, m;
struct st {
	int h, d;
} prev, now;

void solve(){
	scanf("%d%d",&n,&m);
	int mx = 0;
	for (int i = 0; i < m; ++i) {
		scanf("%d%d",&now.d, &now.h);

		if (i == 0) {
			mx = now.h + now.d - 1;
		} else {
			int dd = now.d - prev.d;
			int dh = now.h - prev.h;
			int x = dd+dh, y = dd-dh;
			int c = 0;
			if (x % 2) c = 1;
			int a = (x-c)/2, b = (y-c)/2;
			if (a < 0 || b < 0) {
				printf("IMPOSSIBLE\n");
				return;
			}
			mx = max(prev.h + a, mx);
		}

		swap(prev, now);
	}
	if (prev.d < n) {
		mx = max(mx, prev.h + n - prev.d);
	}
	printf("%d\n",mx);
	return;
}

}

int main() {
	mine::solve();
	return 0;
}