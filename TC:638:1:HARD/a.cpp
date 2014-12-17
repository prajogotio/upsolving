#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

/*WRONG IDEA*/

int dist[203][203];
vector<vector<pair<int,int> > > adj;
vector<int> leaf;
int mark[400003];
int vis[203];

void dfs(int r, int u, int d){
    vis[u] = 1;
    dist[r][u] = d;
    //printf("%d %d dist = %d\n",r, u, dist[r][u]);
    for(int i=0;i<adj[u].size();++i){
        int v = adj[u][i].first;
        int w = adj[u][i].second;
        if(vis[v]) continue;
        dfs(r, v, d+w);
    }
}

class CandleTimer {
public:
    int differentTime(vector<int> A, vector<int> B, vector<int> len){
        int N = A.size();
        leaf.clear();
        for(int i=0;i< 400003; ++i) mark[i] = 0;
        adj = vector<vector<pair<int,int> > > (N+3);
        for(int i=0;i<N;++i){
            adj[A[i]].push_back(make_pair(B[i], len[i]));
            adj[B[i]].push_back(make_pair(A[i], len[i]));
        }
        for(int i=0;i<=N;++i){
            for(int j=0;j<=N;++j) vis[j] = 0;
            dfs(i, i, 0);
            if(adj[i].size() == 1) leaf.push_back(i);
        }
        /*
        for(int i=0;i<=N;++i){
            for(int j=0;j<=N;++j){
                printf("%d ", dist[i][j]);
            }
            printf("\n");
        }
        */
        int a, b, c;
        for(int ii=0;ii<leaf.size();++ii){
            for(int jj=0;jj<leaf.size();++jj){
                if(ii==jj) continue;
                bool can = true;
                int i = leaf[ii];
                int j = leaf[jj];
                //burn L
                for(int kk=0;kk<leaf.size();++kk){
                    if(kk == ii || kk == jj) continue;
                    int k = leaf[kk];
                    int tot = (dist[i][k] + dist[k][j] + dist[i][j])/2;
                    a = tot - dist[k][j];
                    b = tot - dist[i][k];
                    c = tot - dist[i][j];
                    if( !(c <= b || (c >= a && a+b >= c-b)) ){
                        can = false;
                        break;
                    }
                }
                if(can) {
                    //printf("%d %d first %d\n", i, j, 2*dist[i][j]);
                    mark[2*dist[i][j]] = 1;
                }
                can = true;
                //burn L&R
                for(int kk=0;kk<leaf.size();++kk){
                    if(kk == ii || kk == jj) continue;
                    int k = leaf[kk];
                    int tot = (dist[i][k] + dist[k][j] + dist[i][j])/2;
                    a = tot - dist[k][j];
                    b = tot - dist[i][k];
                    c = tot - dist[i][j];
                    if( !( max(a,b) - min(a,b) >= 2*c || 
                    ( c >= min(a,b) && min(a+c, b+c) <= a+b))){
                        can = false;
                        break;
                    }
                }
                if(can) {
                    //printf("%d %d second %d\n", i, j, dist[i][j]);
                    mark[dist[i][j]] = 1;
                }
            }
        }
        int ans = 0;
        for(int i=0;i<=400000;++i){
            if(mark[i]) {
                ++ans;
            }
        }
        return ans;
    }
};

int main(){
    CandleTimer test;
    int a[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
    int b[] = {0,1,2,0,0,0,1,0,0,0,2,5,4,7,13,13,6,15,11,18,19,21,22,16,19,19,20,18,22,27};
    int len[] = {59,58,147,169,34,14,150,55,156,151,130,109,124,15,100,1,156,16,38,97,99,132,150,18,27,91,110,127,15,105};
    /*
    int a[] = {0,0,0,0};
    int b[] = {1,2,3,4};
    int len[] = {123,456,789,1000};
    */
    /*
    int a[] = {0,1,1,2,2,2,6};
    int b[] = {1,4,2,3,6,5,7};
    int len[] = {1,2,3,5,6,4,7};
    */
    int N = sizeof(a) / sizeof(int);
    vector<int> aa(a, a+N);
    vector<int> bb(b, b+N);
    vector<int> cc(len, len+N);
    cout << test.differentTime(aa, bb, cc) << endl;
    return 0;
}