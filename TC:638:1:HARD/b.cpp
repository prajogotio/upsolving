#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

/* using multiple source dijkstra! */
int maxint = (int) 1e8;
int dist[203][203]; // distance between leaves
int d[203];    // distance for dijkstra
int N;              // number of edges
int mark[800003];
vector<vector<pair<int,int> > > adj;
vector<int> len;
vector<int> A;
vector<int> B;

int time_needed() {
    priority_queue<pair<int, int> > pq;
    
    for (int i=0;i<=N;++i){
        if(d[i] == 0) pq.push(make_pair(-d[i], i));
    }
    while(!pq.empty()){
        int cur = -pq.top().first;
        int u = pq.top().second;
        //printf("%d %d\n", u, cur);
        pq.pop();
        if(cur > d[u]) continue;
        for(int i=0;i<adj[u].size();++i){
            int v = adj[u][i].first;
            int w = adj[u][i].second;
            if(d[v] > cur + w) {
                d[v] = cur + w;
                pq.push(make_pair(-d[v], v));
            }
        }
    }
    int max_time = 0;
    for(int i=0;i<N;++i){
        int k = max(d[A[i]], d[B[i]]) - min(d[A[i]], d[B[i]]);
        if( k >= len[i] ) {
            max_time = max(max_time, max(d[A[i]], d[B[i]]) );
        } else {
            max_time = max(max_time, (k + len[i])/2 + min(d[A[i]], d[B[i]]));
        }
    }
    //printf("%d\n", max_time);
    return max_time;
}


class CandleTimer {
public:
    int differentTime(vector<int> tA, vector<int> tB, vector<int> tlen){
        N = tA.size();
        A = tA;
        B = tB;
        len = tlen;
        adj = vector<vector<pair<int,int> > > (N+3);
        for(int i=0;i<N;++i){
            len[i] *= 2;
        }
        for(int i=0;i<=N;++i){
            for(int j=0;j<=N;++j){
                dist[i][j] = maxint;
            }
        }
        for(int i=0;i<=N;++i){
            dist[i][i] = 0;
        }
        for(int i=0;i<N;++i){
            adj[A[i]].push_back(make_pair(B[i], len[i]));
            adj[B[i]].push_back(make_pair(A[i], len[i]));
            dist[A[i]][B[i]] = len[i];
            dist[B[i]][A[i]] = len[i];
        }
        for(int k=0;k<=N;++k){
            for(int i=0;i<=N;++i){
                for(int j=0;j<=N;++j){
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        /*
        for(int i=0;i<=N;++i){
            for(int j=0;j<=N;++j){
                printf("%d ", dist[i][j]);
            }
            printf("\n");
        }
        */
        for(int i=0;i<=800000;++i){
            mark[i] = 0;
        }
        for(int i=0;i<=N;++i){
            for(int j=0;j<=N;++j){
                if(i == j) continue;
                if(adj[i].size() != 1 || adj[j].size() != 1) continue;
                if(mark[dist[i][j]]) continue;
                for(int k=0;k<=N;++k){
                    d[k] = maxint;
                }
                d[i] = 0;
                for(int k=0;k<=N;++k){
                    if(i == k || j == k || adj[k].size() != 1) continue;
                    if(dist[i][j] < dist[j][k]) {
                        d[k] = 0;
                    }
                }
                //printf("first %d %d %d == ", i, j, dist[i][j]);
                if(time_needed() == dist[i][j]) {
                    mark[dist[i][j]] = 1;
                }
            }
        }
        for(int i=0;i<=N;++i){
            for(int j=0;j<=N;++j){
                if(i==j) continue;
                if(adj[i].size()!=1 || adj[j].size()!=1) continue;
                if(mark[dist[i][j]/2]) continue;
                for(int k=0;k<=N;++k){
                    d[k] = maxint;
                }
                d[i] = d[j] = 0;
                for(int k=0;k<=N;++k){
                    if(i==k || k==j || adj[k].size()!=1) continue;
                    if(dist[i][j] <= max(dist[i][k], dist[j][k])) {
                        d[k] = 0;
                    }
                }
                //printf("second %d %d %d == ", i, j, dist[i][j]/2);
                if(time_needed() == dist[i][j]/2) {
                    mark[dist[i][j]/2] = 1;
                }
            }
        }
        int ans = 0;
        for(int i=0;i<=800000;++i){
            if(mark[i]) ++ans;
        }
        return ans;
    }
};

int main(){
    CandleTimer test;
    /*
    int a[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
    int b[] = {0,1,2,0,0,0,1,0,0,0,2,5,4,7,13,13,6,15,11,18,19,21,22,16,19,19,20,18,22,27};
    int len[] = {59,58,147,169,34,14,150,55,156,151,130,109,124,15,100,1,156,16,38,97,99,132,150,18,27,91,110,127,15,105};
    */
    /*
    int a[] = {0,0,0,0};
    int b[] = {1,2,3,4};
    int len[] = {123,456,789,1000};
    */
    int a[] = {0,0,0};
    int b[] = {1,2,3};
    int len[] = {1,1,1};
    /*
    int a[] = {0,1,1,2,3,3,2,4};
    int b[] = {1,2,3,4,5,6,7,8};
    int len[] = {5,3,2,4,6,8,7,1};
    */
    int NN = sizeof(a) / sizeof(int);
    vector<int> aa(a, a+NN);
    vector<int> bb(b, b+NN);
    vector<int> cc(len, len+NN);
    cout << test.differentTime(aa, bb, cc) << endl;
    return 0;
}