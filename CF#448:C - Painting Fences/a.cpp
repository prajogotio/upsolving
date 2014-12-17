#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int MAXINT = (int) 1e9;
int a[5003];
int N;

int minH(int L, int R){
    int ret = MAXINT;
    for(int i=L;i<=R;++i){
        ret = min(ret, a[i]);
    }
    return ret;
}

int rec(int L, int R, int H){
    //printf("%d %d %d\n", L, R, H);
    int MH = minH(L,R);
    int ret = MH - H;
    int prev, state = 0;
    for(int i=L;i<=R;++i){
        if(a[i] > MH && state == 0){
            prev = i;
            state = 1;
        } else if( a[i] == MH && state  == 1){
            ret += rec(prev, i-1, MH);
            state = 0;
        }
    }
    if(state == 1) ret += rec(prev, R, MH);
    return min(R-L+1, ret);
}

int main(){
    cin >> N;
    for(int i=0;i<N;++i){
        cin >> a[i];
    }
    cout << rec(0, N-1, 0) << endl;
    return 0;
}
