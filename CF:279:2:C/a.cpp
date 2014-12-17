#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
using namespace std;

int N;
long long A, B;
string s;
long long p[1000005], q[1000005];

void solve(){
    long long pw = 1;
    p[N] = 0;
    for(int i=N-1;i>=0;--i){
        long long cur = s[i] - '0';
        cur = (cur * pw) % B;
        p[i] = (cur + p[i+1])%B;
        pw *= 10LL;
        pw %= B;
    }
    q[0] = s[0] - '0';
    q[0] %= A;
    for(int i=1;i<N;++i){
        q[i] = (10LL * q[i-1])%A;
        q[i] += (s[i] - '0');
        q[i] %= A;
    }
    for(int i=N-1;i>=1;--i){
        if(p[i] == 0 && q[i-1] == 0 && s[i] != '0'){
            printf("YES\n");
            for(int j=0;j<i;++j){
                printf("%c", s[j]);
            }
            printf("\n");
            for(int j=i;j<N;++j){
                printf("%c", s[j]);
            }
            printf("\n");
            return;
        }
    }
    printf("NO\n");
}

int main(){
    cin >> s;
    cin >> A >> B;
    N = s.size();
    solve();
    return 0;
}