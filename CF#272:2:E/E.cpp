#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;

int INF = 123456;
string s, p;
int N, M;
int next[2003];
int cost[2003];
int dp[2003][2003];

int main(){
    cin >> s;
    cin >> p;
    N = s.size();
    M = p.size();
    for(int i=0;i<N;++i){
        int cur = i;
        int ptr = 0;
        bool complete = false;
        while(cur < N) {
            if(s[cur] == p[ptr]) {
                ++cur;
                ++ptr;
            } else {
                ++cur;
            }
            if(ptr == M){
                complete = true;
                break;
            }
        }
        if(complete){
            next[i] = cur;
            cost[i] = cur - i - M;
        } else {
            next[i] = INF;
            cost[i] = INF;
        }
    }
    /*
    for(int i=0;i<N;++i){
        printf("%d\n", next[i]);
    }
    */
    for(int i=0;i<=N;++i){
        for(int j=0;j<=N;++j){
            dp[i][j] = -INF;
        }
    }
    dp[N][0] = 0;
    for(int i=N-1;i>=0;--i){
        int len = N-i;
        for(int k=0;k<=len;++k){
            dp[i][k] = 0;
            dp[i][k] = max(dp[i][k], dp[i+1][k]);
            if(next[i] != INF && k-cost[i] >= 0) {
                dp[i][k] = max(dp[i][k], 1 + dp[next[i]][k-cost[i]]);
            }
        }
    }
    /*
    for(int j=0;j<N;++j){
        for(int i=0;i<=N;++i){
            if(i!=0) printf(" ");
            if(dp[i][j]!=-INF)printf("%d", dp[j][i]);
            else printf("x");
        }
        printf("\n");
    }
    */
    for(int i=0;i<=N;++i){
        if(i>0)printf(" ");
        printf("%d", dp[0][i]);
    }
    printf("\n");
    return 0;
}
            