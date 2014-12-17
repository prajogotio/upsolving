/*
UPSOLVING:
Codeforces #276 Div. 1 Problem C
*/
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string str;
int P[1000003];
int R[1000003];
int T[1000003];
int onP[1000003];
int onT[1000003];
int onR[1000003];
int ans[1000003];
int res[1000003];
int D, K, N;

void rec_mult(int n){
    if(n==0) return;
    if(n%2==0){
        for(int i=0;i<N;++i){
            onP[P[i]] = i;
        }
        for(int i=0;i<N;++i){
            P[onP[onP[i]]] = i;
        }
        return rec_mult(n/2);
    }else{
        for(int i=0;i<N;++i){
            onR[R[i]] = i;
            onP[P[i]] = i;
        }
        for(int i=0;i<N;++i){
            R[onP[onR[i]]] = i;
        }
        return rec_mult(n-1);
    }
}

void solve(){
    for(int i=0;i<N;++i){
        R[i] = i;
        P[i] = i;
        T[i] = i+1;
    }
    T[N-1] = 0;
    int pos = 0;
    for(int i=0;i<D;++i){
        for(int j=i;j<K;j+=D){
            P[pos++] = j;
        }
    }
    for(int i=0;i<N;++i){
        onP[P[i]] = i;
        onT[T[i]] = i;
    }
    for(int i=0;i<N;++i){
        P[onT[onP[i]]] = i;
    }

    rec_mult(N-K+1);
    /*
    for(int i=0;i<N;++i){
        printf("%d ", R[i]);
    }
    printf("\n");
    */
    int start = N - (N-K+1); 
    pos = 0;
    for(int i=start;;i=(i+1)%N,++pos){
        if(pos!=0 && i==start) break;
        res[pos] = R[i];
    }
    for(int i=0;i<N;++i){
        onR[res[i]] = i;
        onT[ans[i]] = i;
    }
    for(int i=0;i<N;++i){
        ans[onR[onT[i]]] = i;
    }
    for(int i=0;i<N;++i){
        printf("%c", str[ans[i]]);
    }
    printf("\n");
}

int main(){
    int qq;
    cin >> str;
    cin >> qq;
    N = str.size();
    for(int i=0;i<N;++i){
        ans[i] = i;
    }
    while(qq--){
        scanf("%d %d", &K, &D);
        solve();
    }
    return 0;
}