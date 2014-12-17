#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

long long segtree[1000000];
int N, Q;
int head, tail;
int flipped;

void build(int p, int L, int R){
    if(L == R){
        if(L < N) segtree[p] = 1;
        return;
    }
    build(2*p, L, (L+R)/2);
    build(2*p+1, (L+R)/2 + 1, R);
    segtree[p] = segtree[2*p] + segtree[2*p+1];
}

void update(int p, int L, int R, int S, int T, long long val){
    if(R < S || T < L) return;
    if(S <= L && R <= T){
        segtree[p] += val;
        return;
    }
    update(2*p, L, (L+R)/2, S, T, val);
    update(2*p+1, (L+R)/2 + 1, R, S, T, val);
    segtree[p] = segtree[2*p] + segtree[2*p+1];
}

long long query(int p, int L, int R, int S, int T){
    if(R < S || T < L) return -1;
    if(S <= L && R <= T) {
        return segtree[p];
    }
    long long left = query(2*p, L, (L+R)/2, S, T);
    long long right = query(2*p+1, (L+R)/2 + 1, R, S, T);
    if(left == -1) return right;
    if(right == -1) return left;
    return left + right;
}

void fold_tail(int d){
    int c = 2*d-1;
    for(int i = 0; i < d; ++i){
        long long val = query(1, 0, N-1, tail-i, tail-i);
        update(1, 0, N-1, tail-i, tail-i, -val);
        update(1, 0, N-1, tail-c+i, tail-c+i, val);
    }
    tail -= d;
}

void fold_head(int d){
    int c = 2*d-1;
    
    for(int i = 0; i < d; ++i){
        long long val = query(1, 0, N-1, head+i, head+i);
        update(1, 0, N-1, head+i, head+i, -val);
        update(1, 0, N-1, head+c-i, head+c-i, val);
    }
    head += d;
}

void manage_update(int d){
    int c = 2*d-1;
    if(flipped){
        if(2*d > tail -head + 1){
            flipped = 0;
            fold_head(tail-head+1-d);
        } else {
            fold_tail(d);
        }
    } else {
        if(2*d > tail - head + 1){
            flipped = 1;
            fold_tail(tail-head+1-d);
        } else {
            fold_head(d);
        }
    }
}

long long manage_query(int l, int r){
    if(flipped) {
        return query(1, 0, N-1, tail-r+1, tail-l);
    } else {
        return query(1, 0, N-1, head+l, head+r-1);
    }
}

int main(){
    scanf("%d %d", &N, &Q);
    flipped = 0;
    build(1, 0, N-1);
    head = 0, tail = N-1;
    int u,v,type;
    for(int qq = 0; qq < Q; ++qq) {
        scanf("%d", &type);
        if(type == 1){
            scanf("%d", &u);
            manage_update(u);
        } else {
            scanf("%d %d", &u, &v);
            long long ret = manage_query(u, v);
            cout << ret << endl;
        }
    }
    return 0;
}