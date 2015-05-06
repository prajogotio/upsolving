#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

// I AM JUST BEING STUPID.

struct point {
	int x, y;
	point():x(0),y(0){}
	point(int x,int y){
		this->x =x;
		this->y =y;
	}
};

struct qnode {
	qnode *q[4];
	int x1,x2,y1,y2;
	vector<point> arr;
	int X, Y;
	qnode(int x1,int y1,int x2,int y2){
		this->x1=x1;
		this->x2=x2;
		this->y1=y1;
		this->y2=y2;
		X=0;
		Y=0;
	}
	void checkadd(point p){
		if(this->x1<=p.x && p.x<=this->x2 && this->y1<=p.y && p.y<=this->y2){
			arr.push_back(p);
		}
	}
	void split() {
		cover();
		//printf("[%d,%d][%d,%d][%d,%d]\n",x1,y1,x2,y2,X,Y);
		if (x1==x2 && y1==y2){
			return;
		} else if(x1!=x2 && y1!=y2){
			int xm = (x1+x2)/2;
			int ym = (y1+y2)/2;
			q[0] = new qnode(x1,y1,xm,ym);
			q[1] = new qnode(xm+1,y1,x2,ym);
			q[2] = new qnode(x1,ym+1,xm,y2);
			q[3] = new qnode(xm+1,ym+1,x2,y2);
			for(int i=0;i<arr.size();++i){
				for(int j=0;j<4;++j){
					q[j]->checkadd(arr[i]);
				}
			}

			for(int i=0;i<4;++i)q[i]->split();
		} else {
			if(x1==x2){
				int ym = (y1+y2)/2;
				q[0] = new qnode(x1,y1, x1,ym);
				q[1] = new qnode(x1,ym+1, x1,y2);
				for(int i=0;i<arr.size();++i){
					for(int j=0;j<2;++j){
						q[j]->checkadd(arr[i]);
					}
				}

				for(int i=0;i<2;++i)q[i]->split();
			} else {
				int xm = (x1+x2)/2;
				q[0] = new qnode(x1,y1, xm,y1);
				q[1] = new qnode(xm+1,y1, x2,y1);
				for(int i=0;i<arr.size();++i){
					for(int j=0;j<2;++j){
						q[j]->checkadd(arr[i]);
					}
				}

				for(int i=0;i<2;++i)q[i]->split();
			}
		}
	}

	void cover(){
		int a[100005], b[100005];
		for(int i=x1;i<=x2;++i){
			a[i]=0;
		}
		for(int i=y1;i<=y2;++i){
			b[i]=0;
		}
		for(int i=0;i<arr.size();++i){
			a[arr[i].x]=1;
			b[arr[i].y]=1;
		}
		for(int i=x1;i<=x2;++i){
			X += a[i];
		}
		for(int i=y1;i<=y2;++i){
			Y += b[i];
		}
	}
};

qnode* qn;
int N,M,K,Q;

point compute(int x1, int y1, int x2, int y2, qnode* cur){
	if (!cur) {
		return point(0,0);
	}
	printf("%d %d %d %d\n", cur->x1, cur->y1, cur->x2, cur->y2);
	if (cur->x2 < x1 || x2 < cur->x1) {
		if (cur->y2 < y1 || y2 < cur->y1) return point(0,0);
	}
	if (x1 <= cur->x1 && cur->x2 <= x2 &&
		y1 <= cur->y1 && cur->y2 <= y2) {
		return point(cur->X, cur->Y);
	}
	point q[4];
	for (int i=0;i<4;++i){
		q[i] = compute(x1,y1,x2,y2,cur->q[i]);
	}
	point ret(0,0);
	for (int i=0;i<4;++i){
		ret.x += q[i].x;
		ret.y += q[i].y;
	}
	return ret;
}

int main() {
	scanf("%d%d%d%d",&N,&M,&K,&Q);
	int x,y;
	int x1,y1,x2,y2;
	qn = new qnode(1,1,N,M);
	for(int i=0;i<K;++i){
		scanf("%d%d",&x,&y);
		qn->checkadd(point(x,y));
	}
	qn->split();	
	for(int qq=0;qq<Q;++qq){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		if(x1>x2)swap(x1,x2);
		if(y1>y2)swap(y1,y2);
		point res = compute(x1,y1,x2,y2,qn);
		printf("%d %d\n",res.x,res.y);
		if(res.x == x2-x1+1 && res.y == y2-y1+1) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}