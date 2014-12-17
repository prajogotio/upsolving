#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;

string num[100005];
long long Dec[100005];
int N;

bool bsearch(int i){
    if(num[i].size() > num[i+1].size()){
        return false;
    } else if (num[i].size() < num[i+1].size()){
        Dec[i] = 0;
        for(int j=0;j<num[i].size();++j){
            Dec[i] *= 10;
            if(num[i][j] != '?') Dec[i] += (num[i][j] - '0');
            else Dec[i] += 9;
        }
        return true;
    }
    long long cur = 0;
    int nq = 0;
    int pw[10];
    int pwc = 1;
    bool first_digit = false;
    for(int j=1;j<num[i].size();++j){
        pwc *= 10;
    }
    for(int j=0;j<num[i].size();++j){
        cur *= 10;
        if(num[i][j] != '?') cur += (num[i][j] - '0');
        else {
            if(j==0) first_digit = true;
            pw[nq++] = pwc;
        }
        pwc /= 10;
    }
    if(nq == 0){
        Dec[i] = cur;
        return Dec[i] < Dec[i+1];
    }
    int lo = 0, hi = 1, mid;
    long long now;
    int tmp, k;
    for(int j=0;j<nq;++j){
        hi *= 10;
    }
    hi--;
    while(lo <= hi){
        mid = (lo + hi)/2;
        tmp = mid;
        now = cur;
        k = nq-1;
        while(tmp){
            now += tmp%10 * pw[k];
            --k;
            tmp /= 10;
        }
        if(now < Dec[i+1]){
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    if(hi < 0) return false;
    if(hi == 0 && first_digit) return false;
    tmp = hi;
    now = cur;
    k = nq-1;
    while(tmp){
        now += tmp%10 * pw[k];
        --k;
        tmp /= 10;
    }
    if(now < Dec[i+1]){
        Dec[i] = now;
        return true;
    } else return false;
}

int main(){
    scanf("%d", &N);
    for(int i=0;i<N;++i){
        cin >> num[i];
    }
    Dec[N-1] = 0;
    for(int i=0;i<num[N-1].size();++i){
        Dec[N-1] *= 10;
        if(num[N-1][i] != '?') Dec[N-1] += (num[N-1][i] - '0');
        else Dec[N-1] += 9;
    }
    for(int i=N-2;i>=0;--i){
        if(!bsearch(i)){
            printf("NO\n");
            return 0;
        }
    }
    printf("YES\n");
    for(int i=0;i<N;++i){
        printf("%I64d\n", Dec[i]);
    }
    return 0;
}