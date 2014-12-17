#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
double EPS = 1e-12;
double rem[1003];
int x[1003], b[1003];
int par[1003];
int N, L;

bool possible(double R){
    for(int i=0;i<N;++i){
        rem[i] = R*b[i] - sqrt(fabs(.0 + L - x[i]));
        par[i] = -1;
        for(int j=i-1;j>=0;--j){
            double cost = sqrt(fabs(x[i] - x[j] - L));
            if(rem[i] < rem[j] - cost + R*b[i]) {
                rem[i] = rem[j] - cost + R*b[i];
                par[i] = j;
            }
        }
    }
    return (rem[N-1] >= 0);
}

void printout(int i){
    if(par[i] == -1){
        printf("%d", i+1);
        return;
    }
    printout(par[i]);
    printf(" %d", i+1);
}

int main(){
    scanf("%d %d", &N, &L);
    for(int i=0;i<N;++i){
        scanf("%d %d", &x[i], &b[i]);
    }
    double lo = 0, hi = 1e10, mid;
    while(lo < hi) {
        mid = (lo+hi)/2;
        if(possible(mid)) {
            hi = mid - EPS;
        } else {
            lo = mid + EPS;
        }
    }
    possible(lo);
    printout(N-1);
    printf("\n");
    return 0;
}