#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int a[1000003];
int peaks[1000003];
long long dp[1000003];
int N;

long long labs(long long a, long long b){
    long long ret = a-b;
    if(ret < 0) ret = -ret;
    return ret;
}

void solve(){
    int p = N-1;
    int state = 0;
    for(int i=N-2;i>=0;--i){
        if (state == 0){
            if(a[i] < a[i+1]){
                state = 1;
            }
            else if(a[i] > a[i+1]){
                state = -1;
            }
        }
        else if(state == 1){
            if(a[i] > a[i+1]){
                state = -1;
                p = i+1;
            }
        }
        else if(state == -1){
            if(a[i] < a[i+1]){
                state = 1;
                p = i+1;
            }
        }
        peaks[i] = p;
        
    }
    /*
    for(int i=0;i<N-1;++i){
        printf("%d ", peaks[i]);
    }
    printf("\n");
    */
    dp[N-1] = 0;
    for(int i=N-2;i>=0;--i){
        dp[i] = max(labs(a[i], a[peaks[i]]) + dp[peaks[i]+1],
                    labs(a[i], a[peaks[i]-1]) + dp[peaks[i]]);
    }
    cout << dp[0] << endl;
}

int main(){
    scanf("%d", &N);
    for(int i=0;i<N;++i){
        scanf("%d", &a[i]);
    }
    solve();
    return 0;
}