#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
vector<int> a;
int N;
int L;

int main(){
    int u;
    scanf("%d %d", &N, &L);
    for(int i=0;i<N;++i){
        scanf("%d", &u);
        a.push_back(u);
    }
    double hi=1e9, lo = 0, mid, EPS = 1e9;
    sort(a.begin(), a.end());
    while(EPS > 1e-12){
        mid = (lo+hi)/2;
        EPS /= 2;
        bool ok = true;
        for(int i=0;i<N;++i){
            if(i == 0){
                if(a[i] > mid) {
                    ok = false;
                    break;
                }
            }
            if(a[i] - a[i-1] > 2*mid){
                ok = false;
                break;
            }
            if(i == N-1){
                if(L - a[i] > mid) {
                    ok = false;
                    break;
                }
            }
        }
        if(ok){
            hi = mid;
        } else {
            lo = mid;
        }
    }
    printf("%.10lf\n", lo);
    return 0;
}