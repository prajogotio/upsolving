#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

//CODEFORCE #262 Div 2 Problem C
/*
 * Given a_1, a_2, ..., a_n  , M, W
 * and Operation update(i): add 1 to a_i ... a_(i+W)
 * return maximum possible minimum element after M updates
 *
 * Solution: Binary Search + DP
 * Let S[i] be the minimum updates necessary to make each element in A[1..i] >= H
 * S[i+1] >= S[i], and
 * S[i] - S[i-W+1] = amount of updates done in [i-W .. i] which also affect i
 * Similar to 1D Sum Array, but here it is done vertically!
 * You want a fast look up to know what is the total updates done in this last W elements
 * Which is supplied by the 1D Sum Array in O(1)
 * Illustration:
 *  W = 5
 *  1  4  5  9  1  9  4  2  8  1  9  S[i]  (S[i-1] - S[i-W])
 *  1  1  1  1  1                       1
 *     3  3  3  3  3                    4     1 - 0 = 1, add 3
 *        1  1  1  1  1                 5     4 - 0 = 4, add 1
 *           4  4  4  4  4              9     5 - 0 = 5, add 4
 *              0  0  0  0  0           9     9 - 0 = 9, add nothing
 *                 1  1  1  1  1       10     9 - 1 = 8, add 1
 *                    0  0  0  0  0    10    10 - 4 = 6, add nothing
 *                       0  0  0  0    10    10 - 5 = 5, add nothing
 *                          7  7  7    17    10 - 9 = 1, add 7
 *                             0  0    17    17 - 9 = 8, add nothing
 *                                2    19    17 - 10 = 7, add 2
 */
 
#define NMAX 100010
typedef long long llong;

llong Height[NMAX], Sum[NMAX]; //1-indexed
int N, M, W;
llong Cur, Hi, Lo, Mid;

bool check(int Min){
  for(int i=0; i<=N; ++i)
    Sum[i] = 0;
  
  for(int i=1; i<=N; ++i){
    Sum[i] = Sum[i-1];
    
    Cur = Height[i] + Sum[i-1] - Sum[ max(i-W, 0) ];
    if( Cur < Min ){
      Sum[i] += Min - Cur;
    }
  }
  
  return Sum[N] <= M;
}

int main(){
  cin >> N >> M >> W;
  for(int i=1; i<=N; ++i){
    cin >> Height[i];
  }
  Lo = 0, Hi = (llong) 1e9 + (llong) 1e5;
  while ( Lo <= Hi ){
    Mid = (Lo + Hi)/2;
    if( check(Mid) ){
      Lo = Mid + 1;
    } else {
      Hi = Mid - 1;
    }
  }
  cout << Hi << endl;
  return 0;
}