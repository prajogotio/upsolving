#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

vector<vector<int> > stack;
vector<vector<int> > visited;
int val[100005];
int pos[100005];
int vis[100005];
int cnt[100005];
int N;

void arrange(){
    int hi, lo, mid, cur;
    stack.push_back(vector<int>());
    stack[0].push_back(0);
    pos[0] = 0;
    for(int i=1;i<N;++i){
        lo = 0;
        hi = stack.size()-1;
        while(lo <= hi){
            mid = (lo+hi)/2;
            cur = stack[mid].back();
            if(val[cur] < val[i]){
                lo = mid+1;
            } else {
                hi = mid-1;
            }
        }
        if(lo < stack.size()){
            stack[lo].push_back(i);
            pos[i] = lo;
        } else {
            stack.push_back(vector<int>());
            stack[lo].push_back(i);
            pos[i] = lo;
        }
    }
}

void check(){
    int hi,lo,mid,cur, comp;
    int M = stack.size();
    visited = vector<vector<int> >(stack.size()+3);
    for(int i=0;i<stack[M-1].size();++i){
        vis[stack[M-1][i]] = 1;
        ++cnt[pos[stack[M-1][i]]];
        visited[M-1].push_back(stack[M-1][i]);
    }
    for(int k=M-2;k>=0;--k){
        for(int j=0;j<stack[k].size();++j){
            cur = stack[k][j];
            lo = 0; hi = visited[k+1].size()-1;
            while(lo<=hi){
                mid = (lo+hi)/2;
                comp = visited[k+1][mid];
                //printf("%d %d\n", cur, comp);
                if(cur > comp){
                    lo = mid+1;
                } else {
                    hi = mid-1;
                }
            }
            hi = visited[k+1].size()-1;
            //printf("%d %d %d\n", cur, lo, hi);
            while(lo<=hi){
                mid = (lo+hi)/2;
                comp = visited[k+1][mid];
                if(val[cur] >= val[comp]){
                    hi = mid-1;
                } else {
                    vis[cur] = 1;
                    ++cnt[pos[cur]];
                    break;
                }
            }
            if(vis[cur]) visited[k].push_back(cur);
        }
    }
}

void solve(){
    for(int i=0;i<N;++i){
        if(!vis[i]) printf("1");
        else {
            if(cnt[pos[i]] == 1) {
                printf("3");
            } else {
                printf("2");
            }
        }
    }
    printf("\n");
}

int main(){
    scanf("%d", &N);
    for(int i=0;i<N;++i){
        scanf("%d", &val[i]);
        vis[i] = cnt[i] = 0;
    }
    arrange();
    check();
    solve();
    /*
    for(int i=0;i<N;++i){
        printf("%d ", vis[i]);
    }
    printf("\n");
    */
    return 0;
}