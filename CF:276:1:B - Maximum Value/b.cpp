#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int N;
int a[200005];
int m[1000003];
int low[2000003];

void solve(){
    sort(a, a+N);
    int M = 2*a[N-1];
    for(int i=0;i<=M;++i){
        low[i] = -1;
    }
    for(int i=0;i<=1000000;++i){
        m[i] = 0;
    }
    for(int i=0;i<N;++i){
        low[a[i]] = a[i];
        m[a[i]] = 1;
    }
    int prev = -1;
    for(int i=0;i<=M;++i){
        if(low[i] == i){
            low[i] = prev;
            prev = i;
        } else {
            low[i] = prev;
        }
    }
    int ans = 0;
    for(int i=1;i<=1000000;++i){
        if(!m[i]) continue;
        for(int j=2;i*j <= M;++j){
            if(low[i*j] == -1) continue;
            ans = max(ans, low[i*j] % i);
        }
    }
    cout << ans << endl;
}

int main(){
    cin >> N;
    for(int i=0;i<N;++i){
        scanf("%d", &a[i]);
    }
    solve();
    return 0;
}