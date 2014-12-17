#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

int v[2][255][255];
int dp[2][255][255];

class BoardFolding{
public:
    int N;
    int M;
    int b[255][255];
    
    void folder(int state){
        int r, c;
        if(state == 0){
            r = N;
            c = M;
        } else {
            r = M;
            c = N;
        }
        for(int i=0;i<r;++i){
            for(int j=0;j<r;++j){
                v[state][i][j] = 0;
            }
        }
        for(int i=0;i<r;++i){
            for(int j=1;j<=min(i+1,r-i-1);++j){
                int s = i-j+1;
                int t = i+j;
                bool ok = true;
                for(int k=0;k<c;++k){
                    if(state == 0) if(b[s][k] != b[t][k]) ok = false;
                    if(state == 1) if(b[k][s] != b[k][t]) ok = false;
                    if(!ok) break;
                }
                if(ok) v[state][i][j] = 1;
                else break;
            }
        }
        /*
        printf("folder state: %d\n", state);
        for(int i=0;i<r;++i){
            for(int j=0;j<r;++j){
                printf("%d ", v[state][i][j]);
            }
            printf("\n");
        }
        */
    }
    
    void compute(int state, int i, int j){
        //printf("state:%d [%d,%d]\n", state, i, j);
        if(dp[state][i][j] != -1) return;
        if(j-i == 0){
            dp[state][i][j] = 1;
            return;
        }
        dp[state][i][j] = 1;
        for(int k=i;k<=j-1;++k){
            int len_left = k-i+1;
            int len_right = j-k;
            if(len_left == len_right){
                if(v[state][k][len_left]) {
                    compute(state, i, k);
                    compute(state, k+1, j);
                }
            }
            if(len_left < len_right){
                if(v[state][k][len_left]) compute(state, k+1, j);
            }
            if(len_left > len_right){
                if(v[state][k][len_right]) compute(state, i, k);
            }
        }
    }
    
    int getval(char c){
        if('0' <= c && c <= '9'){
            return c - '0';
        }
        if('a' <= c && c <= 'z'){
            return c - 'a' + 10;
        }
        if('A' <= c && c <= 'Z'){
            return c - 'A' + 36;
        }
        if(c == '#') return 62;
        return 63;
    }
    
    int howMany(int N, int M, vector<string> cm){
        this->N = N;
        this->M = M;
        for(int i=0;i<N;++i){
            for(int j=0;j<M;++j){
                b[i][j] = (getval(cm[i][j/6]) >> (j%6))%2;
            }
        }
        //printf("board\n");
        /*
        for(int i=0;i<N;++i){
            for(int j=0;j<M;++j){
                printf("%d ", b[i][j]);
            }
            printf("\n");
        }
        */
        for(int i=0;i<N;++i){
            for(int j=0;j<N;++j){
                dp[0][i][j] = -1;
            }
        }
        for(int i=0;i<M;++i){
            for(int j=0;j<M;++j){
                dp[1][i][j] = -1;
            }
        }
        //printf("\n");
        folder(0);
        folder(1);
        compute(0, 0, N-1);
        compute(1, 0, M-1);
        int x = 0, y = 0;
        for(int i=0;i<N;++i){
            for(int j=i;j<N;++j){
                if(dp[0][i][j] == 1) ++x;
            }
        }
        for(int i=0;i<M;++i){
            for(int j=i;j<M;++j){
                if(dp[1][i][j] == 1) ++y;
            }
        }
        /*
        printf("\n");
        printf("row:\n");
        for(int i=0;i<=N;++i){
            for(int j=0;j<=N;++j){
                printf("%d ", dp[0][i][j]);
            }
            printf("\n");
        }
        printf("col:\n");
        for(int i=0;i<=M;++i){
            for(int j=0;j<=M;++j){
                printf("%d ", dp[1][i][j]);
            }
            printf("\n");
        }
        printf("%d %d\n", x, y);
        */
        return x*y;
    }
};

int main(){
    BoardFolding test;
    int N = 66;
    int M = 1;
    string p[] = {"@", "@", "@", "@", "@", "@", "#", "@", "@", "@", "#", "@", "@", "@", "@", "X", "@", "@", "@", "@", "@", "@", "@", "#", "@", "#", "@", "@", "@", "@", "@", "@", "@", "@", "@", "#", "#", "#", "#", "#", "@", "@", "@", "#", "@", "@", "@", "@", "@", "#", "@", "@", "@", "W", "#", "@", "@", "@", "#", "@", "@", "#", "@", "@", "@", "@"};
    vector<string> a(p, p+N);
    test.howMany(N, M, a);
    return 0;
}