#include <iostream>
#include <cstdio>
#include <algorithm>
#include <deque>
#include <utility>
using namespace std;

deque<pair<long long, int> > dmin, dmax;
long long f[100004];
int a[100004], g[100004];
int N, S, L;
int main(){
    scanf("%d %d %d", &N, &S, &L);
    for(int i=0;i<N;++i){
        scanf("%d", &a[i]);
    }
    int tail = 0;
    dmin.push_back(make_pair(a[0],0));
    dmax.push_back(make_pair(a[0],0));
    g[0] = 0;
    for(int i=1;i<N;++i){
        while (!dmin.empty() && dmin.back().first >= a[i]) {
            dmin.pop_back();
        }
        dmin.push_back(make_pair(a[i],i));
        while(!dmax.empty() && dmax.back().first <= a[i]) {
            dmax.pop_back();
        }
        dmax.push_back(make_pair(a[i],i));
        while(!dmax.empty() && !dmin.empty() && (long long)(dmax.front().first - dmin.front().first) > (long long)S) {
            ++tail;
            if(dmax.front().second < tail) dmax.pop_front();
            if(dmin.front().second < tail) dmin.pop_front();
        }
        g[i] = tail;
    }
    dmin = deque<pair<long long,int> > ();
    for(int i=0;i<L;++i){
        f[i] = 12345678;
    }
    if(L - g[L-1] >= L) f[L-1] = 1;
    else {
        printf("-1\n");
        return 0;
    }
    dmin.push_back(make_pair(0,-1));
    for(int i=L;i<N;++i){
        f[i] = 12345678;
        while(!dmin.empty() && dmin.back().first >= f[i-L]){
            dmin.pop_back();
        }
        dmin.push_back(make_pair(f[i-L],i-L));
        while(!dmin.empty() && dmin.front().second < g[i]-1){
            dmin.pop_front();
        }
        if(!dmin.empty()) f[i] = dmin.front().first + 1;
    }
    if(f[N-1] < (long long)12345678) cout << f[N-1] << endl;
    else printf("-1\n");
    return 0;
}