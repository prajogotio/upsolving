#include <cstdio>
#include <cstdlib>

int main(){
    printf("5000\n");
    for(int i=0;i<5000;++i){
        printf("%d ", (rand()%999 + 1));
    }
    return 0;
}