#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
vector<int> bar;
int main(){
    int N;
    scanf("%d",&N);
    for(int i=0;i<N;++i){
        int k;
        scanf("%d",&k);
        bar.push_back(k);
    }
    int i =0;
    int stroke = 0;
    while(i < N){
        if(bar[i] == 0){ 
            ++i;
            continue;
        }
        int j=i;
        while(j < N && bar[j] != 0) ++j;
        --j;
        int tot = j-i+1;
        if(tot > bar[i]){
            int m=1000000000;
            for(int p=i;p<=j;++p){
                m = min(m,bar[p]);
            }
            for(int p=i;p<=j;++p){
                bar[p]-=m;
            }
            stroke += m;
            //printf("%d\n",stroke);
        } else {
            bar[i] = 0;
            ++stroke;
            //printf("%d\n",stroke);
        }
    }
    printf("%d", stroke);
    return 0;
}