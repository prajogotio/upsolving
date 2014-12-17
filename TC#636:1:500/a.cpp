#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <string>
using namespace std;

/*
X = number of double edges 
E[X] = sum xP(X=x)
P(i-j has double edge)
Given P(X=1), can I get P(X=k) k>1?
or use Indicator function
let I(edge i-j) = 1 if i-j has double edge
if we sort all edges into one sequence
X(i) = I(i-th edge)
E[X] = E[X(i)]
     = sum {i=1 to |E|} E(X(i))
And E(X(i)) = P(ith-edge) since expectation of an indicator is its prability
Now the problem reduces to finding probability of each edges from happening.

Complexity: O(N^2) to perform check for each edge. total O(N^3)
*/


class ClosestRabbit{
public:
    vector<string> board;
    double ncr[403][403];
    int M, N, R;
    int emp;

    int dist(int ia, int ja, int ib, int jb){
        return (ia-ib)*(ia-ib) + (ja-jb)*(ja-jb);
    }
    
    int countAvailable(int ia, int ja, int ib, int jb){
        int ret = 0;
        int mindist = dist(ia, ja, ib, jb);
        for(int i=0;i<M;++i){
            for(int j=0;j<N;++j){
                if(i == ia && j == ja) continue;
                if(i == ib && j == jb) continue;
                if(board[i][j] == '#' || mindist > dist(i,j,ia,ja) || mindist > dist(i,j,ib,jb)){
                    continue;
                }
                if(mindist == dist(i,j,ia,ja)){
                    if(i < ib) continue;
                    if(i == ib && j < jb) continue;
                }
                if(mindist == dist(i,j,ib,jb)){
                    if(i < ia) continue;
                    if(i == ia && j < ja) continue;
                }
                ++ret;
            }
        }
        return ret;
    }
    
    double prob(int ia, int ja, int ib, int jb){
        if(board[ia][ja] == '#' || board[ib][jb] == '#') return 0;
        int avail = countAvailable(ia,ja,ib,jb);
        return ncr[avail][R-2];
    }
    
    double getExpected(vector<string> board, int r){
        this->board = board;
        M = board.size();
        N = board[0].size();
        R = r;
        emp = 0;
        for(int i=0;i<M;++i){
            for(int j=0;j<N;++j){
                if(board[i][j] == '.') ++emp;
            }
        }
        for(int i=0;i<=emp;++i){
            ncr[i][0] = 1;
            if(i>0) ncr[i-1][i] = 0;
        }
        for(int i=1;i<=emp;++i){
            for(int j=i;j>=1;--j){
                ncr[i][j] = ncr[i-1][j] + ncr[i-1][j-1];
            }
        }
        double ans = 0;
        for(int ia=0;ia<M;++ia){
            for(int ja=0;ja<N;++ja){
                for(int ib=0;ib<M;++ib){
                    for(int jb=0;jb<N;++jb){
                        if(ib == ia && jb == ja) continue;
                        ans += prob(ia, ja, ib, jb);
                    }
                }
            }
        }
        return ans/ncr[emp][r]/2.0;
    }
};

int main(){
    ClosestRabbit test;
    string s[5] = {".#####.#####..#....#",
                   "#......#....#.##..##",
                   ".####..#####..#.##.#",
                   ".....#.#...#..#....#",
                   "#####..#....#.#....#"};
    vector<string> tstring;
    tstring.assign(s, s+5);
    printf("%.12lf\n", test.getExpected(tstring, 19));
}