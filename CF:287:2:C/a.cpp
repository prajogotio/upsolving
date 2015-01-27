#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int H;
long long N;
int main() {
	scanf("%d", &H);
	cin >> N;
	long long ans = 0;
	long long lo = 1, hi = 1LL<<H, mid;
	long long h = H;
	int state = 0;
	long long X, Y, A, B;
	while(lo < hi) {
		mid = (lo+hi)/2;
		if(state == 0) {
			X = lo;
			Y = mid;
			A = mid+1;
			B = hi;
		} else {
			X = mid+1;
			Y = hi;
			A = lo;
			B = mid;
		}
		if(X <= N && N <= Y) {
			state = (state+1)%2;
			lo = X;
			hi = Y;
			ans++;
		} else {
			lo = A;
			hi = B;
			ans += (1LL << (h));
		}
		h--;
	}
	cout << ans << endl;
	return 0;
}