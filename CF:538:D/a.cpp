#include <string>
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n;
int a[101][101], temp[101][101];
string b[50];

struct coor {
	int x;
	int y;
	coor(int xx, int yy):x(xx),y(yy){}
};

const coor z(50,50);
bool ok;

void reset(int val=0) {
	for(int i=0;i<101;++i){
		for(int j=0;j<101;++j){
			temp[i][j] = val;
		}
	}

}

inline int translate(int i, int j) {
	return (b[i][j] == 'o' ? 0 : (b[i][j] == 'x' ? 1 : -1));
}

void settmp(int i, int j, int dx, int dy) {
	int tag = translate(i, j);
	temp[z.x+dx][z.y+dy]=tag;
}


void check(int i, int j, int dx, int dy) {
	if(a[z.x+dx][z.y+dy] != 1) return;
	temp[i][j] = a[z.x+dx][z.y+dy];
}

void templ(const coor& c, void (*callback)(int, int, int, int) ) {
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			int dx = i - c.x;
			int dy = j - c.y;
			callback(i, j, dx, dy);
		}
	}
}

void weave() {
	for(int i=0;i<101;++i){
		for(int j=0;j<101;++j){
			if(a[i][j] != temp[i][j]){
				if (temp[i][j] == 0) {

				} else if(a[i][j] == 0) {
					a[i][j] = temp[i][j];
				} else {
					a[i][j] = -1;
				}
			}
		}
	}
}


void print(int a[101][101]) {
	for(int i=z.x-n+1;i<=z.x+n-1;++i){
		for(int j=z.y-n+1;j<=z.y+n-1;++j){
			char c = (a[i][j] == 0 ? '.' : (a[i][j] == 1 ? 'x' : '.'));
			if (i == z.x && j == z.y) {
				c = 'o';
			}
			printf("%c", c);
		}
		printf("\n");
	}
}

int main(){
	scanf("%d",&n);
	ok = true;
	for(int i=0;i<n;++i){
		cin >> b[i];
	}
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			if(b[i][j]=='o') {
				coor cur = coor(i,j);
				reset();
				templ(cur, settmp);
				weave();
			}
		}
	}
	for(int i=0;i<101;++i){
		for(int j=0;j<101;++j){
			if(a[i][j] == 0) a[i][j] = -1;
			if(i == z.x && j == z.y) a[i][j] = 0;
		}
	}
	reset(-1);
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			if(b[i][j] == 'o') {
				coor cur = coor(i,j);
				templ(cur, check);
			}
		}
	}
	// for(int i=0;i<n;++i){
	// 	for(int j=0;j<n;++j) {
	// 		char c = (temp[i][j] == 0 ? '.' : (temp[i][j] == 1 ? 'x' : '.'));
	// 		printf("%c", c);
	// 	}
	// 	printf("\n");
	// }
	for(int i=0;i<n && ok;++i){
		for(int j=0;j<n && ok;++j){
			if(temp[i][j] != translate(i,j) && translate(i,j) != 0) ok = false;
		}
	}

	if(ok) {
		printf("YES\n");
		print(a);
	} else {
		printf("NO\n");
	}
	return 0;
}