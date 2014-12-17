#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int n, x, y;
int gcd(int a, int b){
    if(a < b) {
        return gcd(b, a);
    }
    if(b == 0) return a;
    return gcd(b, a%b);
}

int main(){
    scanf("%d %d %d", &n, &x, &y);
    int g = gcd(x,y);
    x /= g;
    y /= g;
    long long lcd = 1LL * x * y, lo, hi, mid;
    long long len = x + y;
    long long sum = 0;
    int u;
    for(int i=0;i<n;++i){
        scanf("%d", &u);
        //sum += (long long) u;
        long long rem = u % len;
        lo = 0, hi = lcd;
        int state = 2;
        while(lo <= hi){
            mid = (lo+hi)/2LL;
            long long A = mid / (long long) y;
            long long B = mid / (long long) x;
            long long cur = A + B;
            if((mid % (long long) x) == 0LL && (mid % (long long) y) == 0LL){
                cur;
            }
            if(cur == rem) {
                if(A * y > B * x) {
                    state = 0;
                } else if (A * y < B * x) {
                    state = 1;
                }
                break;
            } else if (cur < rem) {
                lo = mid + 1LL;
            } else {
                hi = mid - 1LL;
            }
        }
        if(state == 0) printf("Vanya\n");
        if(state == 1) printf("Vova\n");
        if(state == 2) printf("Both\n");
    }
    return 0;
}