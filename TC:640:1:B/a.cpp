#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

long long f(long long p, long long n1, long long n2, long long ans) {
	return p*p + (n2 - n1 - ans) * p + ans * n1;
}

class MaximumBipartiteMatchingProblem {
public:
	long long solve(int n1, int n2, int ans, int d) {
		long long ret = -1;
		if(ans == n1 || ans == n2) return 1LL*n1*n2;
		if(ans < 2*d) return -1;
		if(n1 < n2) swap(n1, n2);
		double tp = 1.0 * (ans + n1 - n2) / 2.0;
		if(tp <= 0) {
			ret = max(ret, f(ans - d, n1, n2, ans));
		} else {
			ret = max(ret, f(d, n1, n2, ans));
		}
		return ret;
	}
};