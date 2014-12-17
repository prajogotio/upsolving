#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

//WRONG LOGIC NO GOOD


int beg, end;
int N, Q;
long long segtree[400005];
long long lazy[400005];

void build(){
    lazy[1] = 1;
}

void check_propagation(int p, int L, int R){
    if(lazy[p]){
        segtree[p] += lazy[p];
        if(L != R) {
            lazy[2*p] = lazy[p];
            lazy[2*p+1] = lazy[p];
        }
        lazy[p] = 0;
    }
}

long long query(int p, int left, int right, int L, int R){
    if(R < left || right < L) return -1;
    check_propagation(p, L, R);
    if(left <= L && R <= right) {
        printf("%d %d %d\n", L, R, segtree[p]);
        return segtree[p];
    }
    int mid = (L+R)/2;
    long long first = query(2*p, left, right, L, mid);
    long long second = query(2*p+1, left, right, mid+1, R);
    if(first == -1) return second;
    if(second == -1) return first;
    return max(first, second);
}

void lazy_update(int p, int left, int right, int L, int R, long long val) {
    if(R < left || right < L) return;
    check_propagation(p, L, R);
    if(left <= L && R <= right){
        lazy[p] = val;
        return;
    }
    int mid = (L+R)/2;
    lazy_update(2*p, left, right, L, mid, val);
    lazy_update(2*p+1, left, right, mid+1, R, val);
}

void manage_update(int d){
    for(int i = 0; i < d; i++){
        long long val = query(1, beg+i, beg+i, beg, end);
        lazy_update(1, beg+2*d-i-1, beg+2*d-i-1, beg, end, val);
    }
    beg += d;
}

long long manage_query(int l, int r){
    printf("%d %d\n", beg+l, beg+r);
    return query(1, beg+l, beg+r, beg, end);
}

void init(){
    beg = 0;
    end = N-1;
    build();
}

int main(){
    scanf("%d %d", &N, &Q);
    init();
    int type;
    int u, v;
    for(int qq = 0; qq<Q; ++qq){
        scanf("%d", &type);
        if(type == 1){
            scanf("%d", &u);
            manage_update(u);
        }
        else {
            scanf("%d %d", &u, &v);
            long long ret = manage_query(u,v);
            cout << ret << endl;
        }
    }
    return 0;
}