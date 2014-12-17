#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

int adj[1000003];
int mark[1000003];
int pointed[1000003];
int p[200005];
int q[200005];
int N;
int n, m;
int r;

void count(int *a, int &ctr, int root) {
    int cur = root;
    ctr = 0;
    a[ctr++] = root;
    while(adj[cur] != -1 && adj[cur] != 0) {
        cur = adj[cur];
        a[ctr++] = cur;
    }
}

int main(){
    scanf("%d", &N);
    int u, v;
    for(int i=0;i<=1000000;++i) adj[i] = -1;
    for(int i=0;i<N;++i){
        scanf("%d %d", &u, &v);
        mark[u] = mark[v] = 1;
        pointed[v] = 1;
        adj[u] = v;
    }
    for(int i=0;i<=1000000;++i){
        if(mark[i] && !pointed[i]){
            r = i;
            break;
        }
    }
    count(p, n, 0);
    count(q, m, r);
    for(int i=0,j=1,k=0;i+j<=N;k=(k+1)%2){
        if(i+j!=1) printf(" ");
        if(k==0){
            printf("%d", q[i++]);
        } else {
            printf("%d", p[j++]);
        }
    }
    printf("\n");
    return 0;
}