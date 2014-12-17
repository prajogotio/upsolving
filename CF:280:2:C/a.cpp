#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

int n, r, avg;
int u,v;
vector<pair<int,int> > st;
int main(){
    scanf("%d %d %d", &n, &r, &avg);
    long long ctr = 0;
    long long rem = 1LL * avg * n;
    for(int i=0;i<n;++i){
        scanf("%d%d", &u,&v);
        st.push_back(make_pair(v,u));
        rem -= (long long) u;
    }
    if(rem <= 0){
        cout << 0 << endl;
        return 0;
    }
    sort(st.begin(), st.end());
    for(int i=0;i<n;++i){
        long long cur = r - st[i].second;
        if(cur < rem) {
            rem -= cur;
            ctr += cur * st[i].first;
        } else {
            ctr += rem * st[i].first;
            break;
        }
    }
    cout << ctr << endl;
    return 0;
}