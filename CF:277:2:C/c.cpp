#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;

int N, P;
string str;

int iabs(int i){
    return (i >= 0 ? i : -i);
}

int needs(int i){
    int j = N - i - 1;
    int dif = iabs((int)str[i] - (int)str[j]);
    int cdif = 26 - dif;
    //printf("%d %d\n", dif, cdif);
    return min(dif, cdif);
}

void solve(){
    int ans = 0;
    for(int i=0;i<N/2;++i){
        ans += needs(i);
    }
    if(ans == 0) {
        printf("%d", ans);
        return;
    }
    //printf("%d\n", ans);
    P--;
    int L, R;
    if(P < N/2) {
        L = 0;
        R = N/2;
    } else {
        L = N/2;
        R = N;
    }
    int left = 123456, right = -1;
    for(int i=L;i<R;++i){
        if(str[i] != str[N-i-1]){
            left = min(left, i);
            right = max(right, i);
        }
    }
    ans += (right - left) + min(iabs(right - P), iabs(P - left));
    printf("%d\n", ans);
}

int main(){
    scanf("%d %d", &N, &P);
    cin >> str;
    solve();
    return 0;
}