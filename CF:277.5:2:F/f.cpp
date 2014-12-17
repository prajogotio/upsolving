#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int MOD;
int N, M;

long long dp[503][2];
int a[503];
int col[3], row[3];
/*
int compute(int two, int one, int row_two){
    int row_one = two * 2 + one - 2 * row_two;
    if(two == 0 && one == 0 && row_two == 0) return 1;
    if(two == 0 && one == 0) return 0;
    if(row_two < 0 || row_one < 0) return 0;
    if(dp[two][one][row_two] != -1) return dp[two][one][row_two];
    long long ret = 0LL;
    if(two > 0) {
        long long temp = 1LL * row_two * (row_two - 1) / 2 * compute(two-1, one, row_two-2);
        temp %= MOD;
        if(row_one > 0) {
            temp += 1LL * row_two * row_one * compute(two-1, one, row_two-1);
            temp %= MOD;
            temp += 1LL * row_one * (row_one - 1) / 2 * compute(two-1, one, row_two);
            temp %= MOD;
        }
        ret += temp;
        ret %= MOD;
    } else if(one > 0) {
        long long temp = 1LL * row_two * compute(two, one-1, row_two-1);
        temp %= MOD;
        if(row_one>0){
            temp += 1LL * row_one * compute(two, one-1, row_two);
            temp %= MOD;
        }
        ret += temp;
        ret %= MOD;
    }
    dp[two][one][row_two] = ret;
    return ret;
}
*/
int main(){
    int u;
    scanf("%d %d", &N, &M);
    cin >> MOD;
    for(int i=0;i<M;++i){
        for(int j=0;j<N;++j){
            scanf("%1d", &u);
            a[j] += u;
        }
    }
    row[2] = N-M;
    for(int i=0;i<=N;++i){
        for(int k=0;k<2;++k){
            dp[i][k] = 0;
        }
    } 
    dp[0][1] = 1;
    int tot = 0;
    for(int i=0;i<N;++i){
        int cross = 2-a[i];
        tot += cross;
        int cur = (i & 1);
        int prev = (i & 1) ^ 1;
        if(cross == 0) {
            for(int j=0;j<=N;++j){
                dp[j][cur] = dp[j][prev];
            }
        } else if (cross == 1) {
            for(int j=0;j<=N;++j){
                int k = tot - 2*j;
                dp[j][cur] = 0;
                if(j>0){
                    dp[j][cur] += 1LL * j * dp[j-1][prev];
                    dp[j][cur] %= MOD;
                }
                if(k>0){
                    dp[j][cur] += 1LL * k * dp[j][prev];
                    dp[j][cur] %= MOD;
                }
            }
        } else if (cross == 2) {
            for(int j=0;j<=N;++j){
                int k = tot - 2*j;
                dp[j][cur] = 0;
                if(j>1) {
                    dp[j][cur] += 1LL * j * (j-1) / 2 * dp[j-2][prev];
                    dp[j][cur] %= MOD;
                }
                if(k>1) {
                    dp[j][cur] += 1LL * k * (k-1) / 2 * dp[j][prev];
                    dp[j][cur] %= MOD;
                }
                if(j>0 && k>0) {
                    dp[j][cur] += 1LL * j * k * dp[j-1][prev];
                    dp[j][cur] %= MOD;
                }
            }
        }
        
    }
    cout << dp[row[2]][(N-1)&1] << endl;
    //int ans = compute(col[2], col[1], row[2]);
    //cout << ans << endl;
    return 0;
}