#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int H, A, B;
int h, a, b;
int ph, pa, pb;

int main(){
    scanf("%d %d %d %d %d %d %d %d %d", &H, &A, &B, &h, &a, &b, &ph, &pa, &pb);
    int ans = 12345678;
    for(int i=H;i<=1000;++i){
        for(int j=A;j<=1000;++j){
            for(int k=B;;++k){
                int dmg = max(0, a-k);
                int atk = max(0, j-b);
                bool ok = false;
                if(atk == 0) break;
                if(dmg == 0) ok = true;
                else {
                    int k1 = i/dmg;
                    if(i%dmg != 0) ++k1;
                    int k2 = h/atk;
                    if(h%atk != 0) ++k2;
                    if(k1 > k2) ok = true;
                }
                if (ok) {
                    ans = min(ans, ph * (i-H) + pa * (j-A) + pb * (k-B));
                    break;
                }
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}