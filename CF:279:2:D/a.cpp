#include <iostream>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

/*
int ans;
vector<pair<int,int> > S;

void dfs(int a, int b, int m, int n, int depth){
    //printf("%d %d %d %d %d\n", a, b, m, n, depth);
    long long x = 1LL * a * b;
    long long y = 1LL * m * n;
    if(x == y){
        if(ans > depth){
            ans = depth;
            S.clear();
        }
        if(ans == depth){
            S.clear();
            S.push_back(make_pair(a,b));
            S.push_back(make_pair(m,n));
        }
        return;
    }
    if(depth >= ans) return;
    if(x > y){
        if(a%2 == 0){
            dfs(a/2, b, m, n, depth+1);
        } else if(b%2 == 0){
            dfs(a, b/2, m, n, depth+1);
        } 
        if(a%3 == 0){
            dfs((a/3)*2, b, m, n, depth+1);
        } else if(b%3 == 0){
            dfs(a, (b/3)*2, m, n, depth+1);
        }
    } else {
        if(m%2 == 0){
            dfs(a, b, m/2, n, depth+1);
        } else if(n%2 == 0){
            dfs(a, b, m, n/2, depth+1);
        }
        if(m%3 == 0){
            dfs(a, b, (m/3)*2, n, depth+1);
        } else if(n%3 == 0){
            dfs(a, b, m, (n/3)*2, depth+1);
        }
    }
}
*/


int main(){
    int a, b, m, n;
    scanf("%d %d %d %d", &a, &b, &m, &n);
    int two[2], three[2];
    long long rem[2];
    two[0] = two[1] = three[0] = three[1] = 0;
    rem[0] = 1LL * a * b;
    rem[1] = 1LL * m * n;
    for(int i=0;i<2;++i){
        while(rem[i]%2LL == 0 || rem[i]%3LL == 0){
            if(rem[i]%2LL == 0){
                two[i]++;
                rem[i]/=2LL;
            } else if(rem[i]%3LL == 0){
                three[i]++;
                rem[i]/=3LL;
            }
        }
    }
    if(rem[0] != rem[1]){
        printf("-1\n");
    } else {
        int ans = 0;
        if(three[0] < three[1]){
            ans = three[1] - three[0];
            two[1] += ans;
            for(int i=0;i<ans;++i){
                if(m%3==0){
                    m/=3;
                    m*=2;
                } else {
                    n/=3;
                    n*=2;
                }
            }
        } else {
            ans = three[0] - three[1];
            two[0] += ans;
            for(int i=0;i<ans;++i){
                if(a%3==0){
                    a/=3;
                    a*=2;
                } else {
                    b/=3;
                    b*=2;
                }
            }
        }
        if(two[0] > two[1]){
            ans += two[0] - two[1];
            for(int i=0;i<two[0]-two[1];++i){
                if(a%2==0){
                    a/=2;
                } else {
                    b/=2;
                }
            }
        } else {
            ans += two[1] - two[0];
            for(int i=0;i<two[1]-two[0];++i){
                if(m%2==0){
                    m/=2;
                } else {
                    n/=2;
                }
            }
        }
        printf("%d\n", ans);
        printf("%d %d\n%d %d\n", a,b,m,n);
    }    
    return 0;
}