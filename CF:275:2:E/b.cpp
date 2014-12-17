#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <utility>
using namespace std;

string s[51];
double dp[1050000];
long long bm[1050000];
int N, M;

double rec(int cur, long long bitmask, int chosen, int on){
    if(dp[chosen] > -1) return dp[chosen];
    double ret = 0;
    double prob = 1L / (double) (M-on);
    for(int i=0;i<M;++i){
        if(chosen & (1<<i)) continue;
        long long cbm = bitmask;
        int cnt = 0;
        for(int j=0;j<N;++j){
            if(cbm & (1LL << j)){
                if(s[cur][i] != s[j][i]){
                    cbm ^= (1LL << j);
                } else {
                    ++cnt;
                }
            }
        }
        if(cnt == 1) {
            ret += prob;
        } else {
            ret += (rec(cur, cbm, chosen | (1<<i), on+1) + 1L) * prob;
        }
    }
    dp[chosen] = ret;
    return ret;
}

void prep(){
    for(int i=0;i<(1<<M);++i)
        bm[i] = 0;
    for(int i=0;i<N;++i){
        for(int j=i+1;j<N;++j){
            int cur = 0;
            for(int k=0;k<M;++k){
                if(s[i][k] == s[j][k]){
                    cur |= 1<<k;
                }
            }
            bm[cur] |= 1LL<<i;
            bm[cur] |= 1LL<<j;
        }
    }
    for(int i=(1<<M)-1;i>=0;--i){
        for(int j=0;j<M;++j){
            bm[i & (~(1<<j))] |= bm[i];
        }
    }
    
}

double dp2[1050000];

double rec2(int chosen, int m) {
    if(dp2[chosen] > -1) return dp2[chosen];
    double ret = 0;
    double prob = 1.0/(double)(M-m);
    for(int i=0;i<M;++i){
        if(chosen & (1<<i))continue;
        double cnt = 0;
        for(int j=0;j<N;++j){
            if(bm[chosen|(1<<i)] & (1LL<<j))continue;
            ++cnt;
        }
        if(bm[chosen|(1<<i)] != 0){
            ret += (rec2(chosen|(1<<i), m+1) + 1.0) * prob * ((double) N - cnt) /(double)N + (cnt)/(double)N * prob;
        } else {
            ret += prob;
        }
    }
    //printf("%d %d %lf\n", chosen, m, ret);
    dp2[chosen] = ret;
    return ret;
}

int main(){
    cin >> N;
    for(int i=0;i<N;++i){
        cin >> s[i];
    }
    M = s[0].size();
    int lim = 1<<M;
    double prob = 1L / ((double) N);
    double ans = 0;
    for(int i=0;i<N;++i){
        for(int j=0;j<lim;++j) dp[j] = -3;
        ans += rec(i, (1LL << N)-1, 0, 0) * prob;
    }
    /*
    prep();
    for(int i=0;i<(1<<M);++i) dp2[i] = -3;
    ans = rec2(0,0);
    */
    printf("%.12lf\n", ans);
    return 0;
}