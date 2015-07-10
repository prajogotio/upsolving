#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cassert>
using namespace std;

/*
new problem solving strategy.
Observe monotonicity property of the problem.

Start off with the plain DP strategy:
let dp[k][i] be the minimum value if getting the first i people into k groups.
then dp[k][i] = min { dp[k-1][j] + val[j+1][i] } for j in k-1 to i-1
This is an O(KN^2) solution.

Now let opt[k][i] be the smallest value of j that minimizes dp[k][i].
Claim: opt[k][i] <= opt[k][i+1]
Proof:
let opt[k][i] = j1 and opt[k][i+1] = j2. we will proof by contradiction
assume j1 > j2, we have:
dp[k-1][j1] + val[j1+1][i] < dp[k-1][j2] + val[j2+1][i]
and
dp[k-1][j1] + val[j1+1][i+1] > dp[k-1][j2] + val[j2+1][i+1]
Hence we have:
val[j1+1][i+1] - val[j1+1][i] >= val[j2+1][i+1] - val[j2+1][i]
we want to show that LHS is actually <= RHS
_______________________
|        |    |    |  |
|        |    |    |  | 
|        |    |    |  |
|______j2|____|____|__|_
|        |    |    |  |
|        |    |    | y|
|________|__j1|____|__|_
|        |    |    |  |
|        |    |    | x|
|________|____|__ i|__|_
|        |    |    |  |
|        |  y |  x | x|
|________|____|____i+1|_
         |    |    |  |

The area marked by x is shared by both LHS and RHS
but y is only owned by RHS
since RHS >= 0, it follows that LHS should have been <= RHS. (shown)

hence we have opt[k][i] <= opt[k][i+1] for all i

The monotonicity of opt[k][i] suggests that we can break the problem into
subproblems that are exclusive of each other. 

Let D(int k, int L, int R, int left, int right) be an operation:
1. let M = (L+R)/2 the mid point of L and R
2. it is known that opt[k][M] is in [left, right].
3. iterate through [left, right] to find dp[k][M] and opt[k][M]
4. now break the interval (L, R) into two:
   4.1 (L, M-1): by monotonicity of opt, we know that opt[k][i] <= opt[k][M]
               for i = L to M-1
        so we recursively do D(k, L, M-1, left, opt[k][M])
   4.2.(M+1, R): by monotonicity of opt, we know that opt[k][i] >= opt[k][M]
               for i = M+1 to R
        so we recursively do D(k, M+1, R, opt[k][M], right)

To solve the problem we iterate through all value of k.

Complexity:
let the depth of the recursion be d.
since in each level of (d, L, R, left, right) we will perform O(right-left) operations,
at each depth d, there is in total O(N) operations performed (since each [left,right] are exclusive
of one another, sharing at most 1 element)
furthermore, d will be O(log N), hence in total D(k, L, R, left, right) will do O(N log N) operations
for each k. Hence the total complexity of this solution will be O(K N log N).

*/

namespace cf {
int dp[810][4010];
int sum[4010][4010];
int N, K;

int val(int j, int i) {
	return (sum[i][i] + sum[j-1][j-1] - sum[i][j-1]*2)/2;
}

void dfs(int k, int L, int R, int left, int right) {
	if(L>R)return;
	int i = (L+R)/2;
	dp[k][i] = 12345678;
	int opt = -1;
	for (int j = left; j <= right; ++j) {
		if (j+1>i) break;
		if (k-1>j) continue;
		if (dp[k][i] > dp[k-1][j] + val(j+1, i)) {
			dp[k][i] = dp[k-1][j] + val(j+1, i);
			opt = j;
		}
	}
	assert(dp[k][i] >= 0);
	//assert(opt!=-1);
	if(L==R) {
		return;
	}
	dfs(k, L, i-1, left, opt);
	dfs(k, i+1, R, opt, right);
}

char buffer[100000];

void solve() {
	scanf("%d%d\n",&N,&K);

	for(int i=1;i<=N;++i){
		gets(buffer);
		for(int j=1;j<=N;++j){
			sum[i][j] = buffer[(j-1)*2]-'0';
			sum[i][j] += sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
		}
	}
	for(int i=1;i<=N;++i){
		dp[1][i] = sum[i][i]/2;
	}
	for(int k=2;k<=K;++k){
		dfs(k, k, N, 1, N);
	}
	printf("%d\n", dp[K][N]);
}

}

int main(){
	cf::solve();
	return 0;
}