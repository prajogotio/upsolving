#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
using namespace std;

pair<int,int> segtree[400100][13];
char b[100400][19];
int N,M,Q;

void compute(int p, int row){
    for(int i=0;i<=M+1;++i){
        segtree[p][i] = make_pair(row, 12);
    }
    for(int i=1;i<=M;++i){
        if(b[row][i-1] == '<'){
            segtree[p][i] = make_pair(row, 0);
        } else break;
    }
    for(int i=M;i>=1;--i){
        if(b[row][i-1] == '>'){
            segtree[p][i] = make_pair(row, M+1);
        } else break;
    }
    for(int i=1;i<=M;++i){
        if(b[row][i-1] == '^'){
            segtree[p][i] = make_pair(row-1, i);
            for(int j=i-1;j>=1;--j){
                if(b[row][j-1] == '>'){
                    segtree[p][j] = make_pair(row-1, i);
                } else break;
            }
            for(int j=i+1;j<=M;++j){
                if(b[row][j-1] == '<'){
                    segtree[p][j] = make_pair(row-1, i);
                } else break;
            }
        }
    }
    /*
    printf("row: %d\n", row);
    for(int i=1;i<=M;++i){
        printf("(%d,%d) ", segtree[p][i].first, segtree[p][i].second);
    }
    printf("\n");
    */
}

void combine(int p, int L, int R){
    int mid = (L+R)/2;
    for (int i=1;i<=M;++i){
        pair<int,int> P = segtree[2*p+1][i];
        if(mid+1 <= P.first){
            segtree[p][i] = P;
        } else {
            segtree[p][i] = segtree[2*p][P.second];
        }
    }
}

void build(int p, int L, int R){
    if(L==R){
        compute(p, L);
        return;
    }
    int mid = (L+R)/2;
    build(2*p, L, mid);
    build(2*p+1, mid+1, R);
    combine(p, L, R);
}

void update(int p, int S, int L, int R){
    if(R < S || S < L)return;
    if(S == L && L == R) {
        compute(p, S);
        return;
    }
    int mid = (L+R)/2;
    update(2*p, S, L, mid);
    update(2*p+1, S, mid+1, R);
    combine(p, L, R);
}

pair<int, int> query(int p, pair<int,int> q, int L, int R){
    //printf("q=(%d,%d) [%d,%d]\n", q.first, q.second, L, R);
    if(q.first == L && R == L){
        return segtree[p][q.second];
    }
    int mid = (L+R)/2;
    if(q.first <= mid){
        return query(2*p, q, L, mid);
    } else {
        pair<int,int> tmp = query(2*p+1, q, mid+1, R);
        if(tmp.second == 12 || mid+1 <= tmp.first) return tmp;
        return segtree[2*p][tmp.second];
    }
}

int main(){
    scanf("%d %d %d", &N, &M, &Q);
    for(int i=0;i<N;++i){
        scanf("%s",b[i]);
    }
    build(1, 0, N-1);
    char ch, ty;
    int u, v;
    for(int qq=0;qq<Q;++qq){
        scanf(" %c %d %d", &ty, &u, &v);
        if(ty == 'A'){
            pair<int,int> ret = query(1, make_pair(u-1,v), 0, N-1);
            if(ret.second == 12) printf("-1 -1\n");
            else printf("%d %d\n", ret.first+1, ret.second);
        } else {
            scanf(" %c", &ch);
            b[u-1][v-1] = ch;
            update(1, u-1, 0, N-1);
        }
    }
    return 0;
}