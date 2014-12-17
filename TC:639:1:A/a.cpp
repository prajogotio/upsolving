#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

class AliceGame {
public:
    bool check(int n, int lim, long long val){
        if(n > lim) return false;
        long long sum = 1LL * n * (n+1) / 2LL;
        if(sum > val) return false;
        long long rem = val - sum;
        if(rem == 0) return true;
        long long eq = rem/(long long) n;
        if(rem % ((long long) n) != 0) ++eq;
        if(eq + n > (long long) lim) return false;
        return true;
    }
    long long findMinimumValue(long long x, long long y){
        //special case: x or y = 0;
        int hi=2000000, lo=0, mid;
        long long tmp;
        bool found = false;
        while(lo<=hi){
            mid = (lo+hi)/2;
            tmp = 1LL * mid * mid;
            if(tmp == (x+y)){
                lo = mid;
                found = true;
                break;
            } else if(tmp < x+y){
                lo = mid+1;
            } else {
                hi = mid-1;
            }
        }
        if(!found) return -1;
        if(x == 0LL) return 0;
        for(int i=1;i<=lo;++i){
            if((x+i)%2LL != 0) continue;
            tmp = (x+i)/2LL;
            if(check(i, lo, tmp)){
                return i;
            }
        }
        return -1;
    }
};