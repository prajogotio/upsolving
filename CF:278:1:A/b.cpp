#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int H,A,B,h,a,b,ph,pa,pb;
int main(){
    scanf("%d%d%d%d%d%d%d%d%d", &H,&A,&B,&h,&a,&b,&ph,&pa,&pb);
    int ans = 12345678;
    for(int i=A;;++i){
        for(int j=B;;++j){
            int atk = max(0, i-b);
            int dmg = max(0, a-j);
            if(atk!=0){
                int k = h/atk;
                if(h%atk != 0) ++k;
                int hp = k*dmg + 1;
                if(hp < H) hp = H;
                ans = min(ans, ph * (hp-H) + pa * (i-A) + pb * (j-B));
            }
            if(j>=a) break;
        }
        if(i>=h+b) break;
    }
    printf("%d\n", ans);
    return 0;
}