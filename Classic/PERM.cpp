#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

/*
====== Classic problem statement ======
Given a permutation P[1..n] of [1..n], 
find the number of segments [i..j] such that
max[P[i]..P[j]] - min[P[i]..P[j]] = j - i
or in other words, when P[i..j] is sorted,
the resulting P'[i..j] has the property P'[k] + 1 = P'[k+1]
for all k in [i..j)

====== Solution ======
Let max[i][j] be the maximum element in P[i..j],
    min[i][j] be the minimum element in P[i..j],
and val[i][j] = max[i][j] - min[i][j] + i - j

The problem statement is hence equivalent to:
find the number of segments [i..j] s.t. val[i][j] = 0

Suppose we already know val[i][j-1], max[i][j-1] and min[i][j-1].
Then val[i..j] can be written as:

val[i][j] = max(max[i][j-1], P[j]) - min(min[i][j-1], P[j]) + i - j

Now we have:
  val[i][j]              - val[i][j-1] =
  max(max[i][j-1], P[j]) - max[i][j-1]     ..............(1)
- min(min[i][j-1], P[j]) - (-min[i][j-1])  ..............(2)
+ i                      - i               ..............(3)
- j                      - (-(j-1))        ..............(4)
for all i in [1..j)
(3) evaluates to 0 and (4) evaluates to -1.

Hence simplified:
val[i][j] = val[i][j-1] + (1) + (2) + (3) + (4)
where (1) = max(max[i][j-1], P[j]) - max[i][j-1]
      (2) = - min(min[i][j-1], P[j]) + min[i][j-1]
      (3) = 0
      (4) = -1
Furthermore, we know that val[j][j] = 0.

Now suppose we have array a[1..n] s.t. a[i] holds the value of val[i][j-1].
We want to convert a[i] to hold the value of val[i][j] instead.

Let update(i, j, v) be an operation of increasing a[i..j] by v. Hence
we need to do operations for each (1), (2) and (4).

(4) can be easily done: all i from 1 to j-1 needs to be decremented by 1, 
hence we can do update(1, j-1, -1).

We don't need to do anything for (3).

Now we focus on (1) and (2).
We turn to the this observation:
If a[j] > max[i][j-1], then for all i' > i, we have a[j] > max[i'][j-1].
Similarly if a[j] < min[i][j-1], then for all i' > i, a[j] < min[i'][j-1].

Focus on (1). Suppose we are considering segment [1..j]. Eg
i     1 2 3 4 5 6 7 8 9
P     4 7 9 5 2 8 1 6 3
      xxxxx              9 [1..3]
            xxxxx        8 [4..6]
                  xxx    6 [7..8]
                      x  3 [9..9]
To store this information, we use a monotonic stack Smax where:
1. Smax store the index of an element in P
2. P[Smax[i]] < P[Smax[i-1]]
3. max[Smax[i-1]+1 ... Smax[i]] = P[smax[i]]

To evalute (1), we do:
1. For each segment in Smax, if P[j] is larger than P[Smax[i]],
   update(L, R, -P[Smax[i]]) where L and R is the left and right boundary
   of Smax[i].
2. update(P[Smax.top], i-1, P[j]).
3. The rest of the segments in Smax are hence larger than P[j] and hence the value for
   (1) are not affected on those segments. 
4. Push j.

Perform symmetrical analysis on (2) (by similarly creating a monotonic stack called Smin)
and we will get a[i] to be the value of val[i][j].
Now we can compute the number of suffixes in [1..j] such that val[i][j] = 0.
We perform this for all prefixes and the total will be the answer.

===== Subpart of the problem ======
Given a[1..n], an operation update(i,j,v) done lazily. Support query(i,j) to find
the number of elements in a[i..j] that are equal to 0.

First notice that val[i][j] >= 0 for any i,j. This proves to be very useful.

Let's define MV a segment tree which support the following operations:
1. query(i, j) returns the (minVal, count), where:
   - minVal is the minimum value in a[i..j] 
   - count is the number of occurance of minVal in a[i..j]
2. update(i, j, val) which increments a[i..j] by val.

MV implements lazy updates and lazy propagation. We use the following relationship
between nodes in the segment tree:
1. consider a node in the segment tree with range [L, R], call this par.
2. let the children be left and right, where left is [L, M] and right is [M+1, R]. M is the
   middle of L and R, naturally.
3. Then par.minVal will be min(left.minVal, right.minVal), and
   par.count = (par.minVal == left.minVal ? left.count : 0)
             + (par.minVal == right.minVal ? right.count : 0)
We can do lazy updates on this segment tree because when we increment a segment [L, R] by val,
the relative order of the elements in [L, R] does not change, only that the minVal of that segment
is changed by val. Furthermore, count does not change as a corollary.
Since changes on an entire segment [L, R] can be done in O(1), which allows lazy updates to be
implemented efficiently.

If we initialize all nodes in MV with minVal = 1 and count them accordingly,
whenever we completed the updates on each j from val[i][j-1] to val[i][j], the
root of MV will have the total number of zeroes in val[i][j], because 0 must be
the lowest possible value in each iteration of val[i][j]. However, sometimes the
minVal of root might be bigger than 0, i.e. there are no 0s in val[i][j], hence
we must check accordingly.


===== Complexity =====
Since elements can only be pushed and popped at most once into Smin and Smax, these
operations requires O(N) time.
To update a[i], we use segment tree, with lazy update. By performing a lazy update procedure,
all the required updates can be done in O(N lg N) time.
To compute the number of 0s in a[i], we also use segment tree. With lazy propagation,
all queries can be performed in O(N lg N) time.

*/

namespace solution {

const int N = 300010;
int n;
int P[N];
int minVal[4*N], count[4*N], lazy[4*N];
vector<int> Smax, Smin;

void init(int p, int L, int R) {
    if (L==R) {
        count[p] = 1;
        minVal[p] = 1;
        return;
    }
    int M = (L+R)/2;
    init(2*p, L, M);
    init(2*p+1, M+1, R);
    minVal[p] = 1;
    count[p] = count[2*p] + count[2*p+1];
}

void propagate(int p, int L, int R) {
    minVal[p] += lazy[p];
    if (L!=R) {
        lazy[2*p] += lazy[p];
        lazy[2*p+1] += lazy[p];
    }
    lazy[p] = 0;
}

void upd(int p, int L, int R, int S, int T, int val){
    if(R<S || T<L) return;
    if(S<=L && R<=T) {
        lazy[p] += val;
        return;
    }
    propagate(p, L, R);
    int M = (L+R)/2;
    upd(2*p, L, M, S, T, val);
    upd(2*p+1, M+1, R, S, T, val);
    int left = minVal[2*p]+lazy[2*p];
    int right = minVal[2*p+1]+lazy[2*p+1];
    int mv = min(left, right);
    count[p] = (mv == left ? count[2*p] : 0) + (mv == right ? count[2*p+1] : 0);
    minVal[p] = mv;
}

void initTree() {
    init(1, 0, n-1);
}

void update(int L, int R, int val) {
    if(L>R) return;
    upd(1, 0, n-1, L, R, val);
}


void solve(){
    scanf("%d", &n);
    int x,y;
    for(int i=0;i<n;++i){
        scanf("%d%d",&x,&y);
        P[x-1]=y-1;
    }
    initTree();
    long long ans = 1;
    Smax.push_back(0);
    Smin.push_back(0);
    update(0,0,-1);
    for(int i=1;i<n;++i){
        update(0,i,-1);
        int prev = i;
        while(!Smax.empty() && P[Smax.back()] < P[i]) {
            int k = Smax.back();
            Smax.pop_back();
            int L = 0;
            if (!Smax.empty()) {
                L = Smax.back()+1;
            }
            update(L, prev-1, -P[k]);
            prev = L;
        }
        update((!Smax.empty() ? Smax.back()+1 : 0), i-1, P[i]);
        Smax.push_back(i);

        prev = i;
        while(!Smin.empty() && P[Smin.back()] > P[i]) {
            int k = Smin.back();
            Smin.pop_back();
            int L = 0;
            if (!Smin.empty()) {
                L = Smin.back()+1;
            }
            update(L,prev-1,P[k]);
            prev = L;
        }
        update((!Smin.empty() ? Smin.back()+1 : 0), i-1, -P[i]);
        Smin.push_back(i);

        if(lazy[1]+minVal[1] == 0) ans += count[1];
    }
    cout << ans << endl;
    return;
}

}

int main(){
    solution::solve();
	return 0;
}