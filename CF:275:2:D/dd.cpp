#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
using namespace std;

int N, M;
int a[100003][33];
int q[100003][33];
int l[100003];
int r[100003];
int segtree[400003][33];
int lazy[400003][33];

void build(int tree, int p, int L, int R) {
    if(L > R) return;
    if(L == R) {
        segtree[p][tree] = a[L][tree];
        return;
    }
    int mid = (L+R)/2;
    build(tree, p*2, L, mid);
    build(tree, p*2+1, mid+1, R);
    segtree[p][tree] = segtree[2*p][tree] & segtree[2*p+1][tree];
}

int query(int tree, int p, int L, int R, int M, int N) {
    if(R < M || N < L) return -1;
    if(lazy[p][tree]) {
        return 1;
    }
    if(M <= L && R <= N) return segtree[p][tree];
    int mid = (L+R)/2;
    int left = query(tree, 2*p, L, mid, M, N);
    int right = query(tree, 2*p+1, mid+1, R, M, N);
    if(left == -1) return right;
    if(right == -1) return left;
    return left & right;
}

void lazy_update(int tree, int p, int L, int R, int M, int N) {
    //printf("%d %d %d %d\n", L, R, M, N);
    if(R < M || N < L) return;
    if(lazy[p][tree]) {
        return;
    }
    if(M <= L && R <= N) {
        lazy[p][tree] = 1;
        return;
    }
    int mid = (L+R)/2;
    lazy_update(tree, 2*p, L, mid, M, N);
    lazy_update(tree, 2*p+1, mid+1, R, M, N);
}

void init(int tree){
    build(tree, 1, 0, N-1);
}

int qqq[100003];
int res[100003];
int fintree[400003];

void build2(int p, int L, int R) {
    if(L>R) return;
    if(L==R){
        fintree[p] = res[L];
        return;
    }
    int mid = (L+R)/2;
    build2(p*2, L, mid);
    build2(p*2 + 1, mid+1, R);
    fintree[p] = fintree[2*p] & fintree[2*p+1];
}

int query2(int p, int L, int R, int M, int N){
    if(R < M || L > N) return -1;
    if(M<=L && R<=N) {
        return fintree[p];
    }
    int mid = (L+R)/2;
    int left = query2(2*p, L, mid, M, N);
    int right = query2(2*p+1, mid+1, R, M, N);
    if(left == -1) return right;
    if(right == -1) return left;
    return left & right;
}

int main(){

    cin >> N >> M;
    int qq;
    for(int i=0;i<M;++i){
        scanf("%d %d %d", &l[i], &r[i], &qqq[i]);
        qq = qqq[i];
        for(int j=0;j<30;++j){
            q[i][j] = qq%2;
            qq /= 2;
        }
        --l[i];
        --r[i];
    }
    for(int i=0;i<30;++i){
        init(i);
    }
    for(int i=0;i<M;++i){
        for(int j=0;j<30;++j){
            if(q[i][j] == 1) {
                lazy_update(j, 1, 0, N-1, l[i], r[i]);
            }
        }
    }
    for(int i=0;i<N;++i){
        res[i] = 0;
        for(int j=29;j>=0;--j){
            res[i] *= 2;
            res[i] += query(j, 1, 0, N-1, i, i);
        }
    }
    
    build2(1, 0, N-1);
    
    bool ok = true;
    for(int i=0;i<M;++i){
        if(query2(1, 0, N-1, l[i], r[i]) != qqq[i]) {
            ok = false;
            break;
        }
    }
    if(ok){
        printf("YES\n");
        for(int i=0;i<N;++i){
            if(i!= 0) printf(" ");
            printf("%d", res[i]);
        }
        printf("\n");
    } else {
        printf("NO\n");
    }
    return 0;
}