#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;

/*
n = 2f + 3e
n-2f  1/3 >= 1/2 f f-1
n/3 >= 1/2 f^2 - 1/2 f + 2/3f
n/3 >= 1/2 f^2 + 1/6 f
2n >= 3 f^2 + f
turning point : f = -1/6
*/

int main(){
	long long n;
	cin >> n;
	long long lo = 0, hi = n-1, mid;
	while(lo <= hi){
		mid = (lo+hi)/2;
		if(2.0*n < mid + 3.0 * mid * mid) {
			hi = mid - 1;
		} else {
			lo = mid + 1;
		}
	}
	long long R = (n+hi)/3;
	long long L = (n)/3;
	cout << (R-L) << endl;
	return 0;
}