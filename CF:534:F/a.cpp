#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int vis[11][32][7776], vis2[11][32][7776], n, m, a[20], b[20];
int par[11][32][7776], par2[11][32][7776], bd[6][21];
int sz = 1;


void compute(int vis[11][32][7776], int kmax, int offset, int par[11][32][7776]) {
	// printf("kmax=%d offset=%d\n", kmax, offset);
	for(int k=0;k<kmax;++k){
		for(int bm=0;bm<(1<<n);++bm){
			for(int s=0;s<sz;++s){
				if(vis[k][bm][s]){
					// printf("======= %d\n", k);
					// for(int i=0;i<n;++i){
						// if(bm & (1<<i))printf("*");
						// else printf(".");
					// }
					// printf("\n");
					// printf("pembanding\n");
					for(int next=0;next<(1<<n);++next){
						int ch = 0;
						int x[5] = {0,0,0,0,0};
						bool set = false;
						for(int i=0;i<n;++i){
							if(next & (1<<i)){
								// printf("*");
								if (!set){
									set = true;
									++ch;
								}
								if (!(bm & (1<<i))) {
									x[i] = 1;
								}
							} else {
								// printf(".");
								set = false;
							}
						}
						// printf("(%d, %d)\n", ch, b[k+offset]);
						if(ch != b[k+offset]) continue;
						int ss = 0;
						int tmp = s;
						int y[5] = {0,0,0,0,0};
						for (int i=n-1;i>=0;--i){
							y[i] = tmp%6;
							tmp /= 6;
						}
						for (int i=0;i<n;++i){
							ss *= 6;
							ss += x[i]+y[i];
						}
						// printf("[%d bm=%d ss=%d] ok\n", k+1, next, ss);
						vis[k+1][next][ss]=1;
						par[k+1][next][ss]=k*(1<<n)*sz + bm*sz + s;
					}
				}
			}
		}
	}
}

void printAnswer(int lf, int s, int rg, int ss){
	int cur = (m/2)*(1<<n)*sz+lf*sz+s;
	while(cur != 0) {
		int k = cur/((1<<n) * sz);
		int bb = (cur - k * ((1<<n) * sz))/sz;
		int ss = (cur - k * ((1<<n) * sz) - bb*sz);
		// printf("%d %d %d\n", k, bb, ss);
		for(int i=0;i<n;++i){
			bd[i][k] = (bb & (1<<i));
		}
		cur = par[k][bb][ss];
	}
	cur = (m-m/2)*(1<<n)*sz+rg*sz+ss;
	while(cur!=0){
		int k = cur/((1<<n) * sz);
		int bb = (cur - k * ((1<<n) * sz))/sz;
		int ss = (cur - k * ((1<<n) * sz) - bb*sz);
		// printf("%d %d %d\n",k, bb, ss);
		for(int i=0;i<n;++i){
			bd[i][m-k+1] = (bb & (1<<i));
		}
		cur = par2[k][bb][ss];
	}
	for(int i=0;i<n;++i){
		for(int j=1;j<=m;++j){
			if(bd[i][j])printf("*");
			else printf(".");
		}
		printf("\n");
	}
}


int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;++i)scanf("%d",&a[i]), sz*=6;
	for(int i=0;i<m;++i)scanf("%d",&b[i]);
	vis[0][0][0] = vis2[0][0][0] = 1;
	compute(vis, m/2, 0, par);
	// int goal = 0;
	// for(int i=0;i<n;++i){
	// 	goal *= 6;
	// 	goal += a[i];
	// }
	// for(int bm=0;bm<(1<<n);++bm){
	// 	for(int s=0;s<sz;++s){
	// 		if(s!=goal)continue;
	// 		if(vis[m][bm][s]){
	// 			//printf("%d %d %d\n",m, bm, s);
	// 			int cur = m*(1<<n)*sz+bm*sz+s;
	// 			while(cur != 0) {
	// 				int k = cur/((1<<n) * sz);
	// 				int bb = (cur - k * ((1<<n) * sz))/sz;
	// 				int ss = (cur - k * ((1<<n) * sz) - bb*sz);
	// 				//printf("%d %d %d\n", k, bb, ss);
	// 				for(int i=0;i<n;++i){
	// 					bd[i][k] = (bb & (1<<i));
	// 				}
	// 				cur = par[k][bb][ss];
	// 			}
	// 			for(int i=0;i<n;++i){
	// 				for(int j=1;j<=m;++j){
	// 					if(bd[i][j])printf("*");
	// 					else printf(".");
	// 				}
	// 				printf("\n");
	// 			}
	// 			return 0;
	// 		}
	// 	}
	// }
	reverse(b+m/2, b+m);
	compute(vis2, m - m/2, m/2, par2);
	for(int lf=0;lf<(1<<n);++lf){
		for(int s=0;s<sz;++s){
			if(!vis[m/2][lf][s])continue;
			// printf("%d %d %d\n",m/2, lf, s);
			int x[5]={0,0,0,0,0};
			int tmp = s;
			// printf("xs\n");
			for(int i=n-1;i>=0;--i){
				x[i] = tmp%6;
				tmp/=6;
			}
			// for(int i=0;i<n;++i){
			// 	printf("%d ",x[i]);
			// }
			// printf("\n[][][]\n");
			for(int rg=0;rg<(1<<n);++rg){
				int y[5] = {0,0,0,0,0};
				bool ok = true;
				// printf("%d == %d\n",lf, rg);
				for(int i=0;i<n;++i){
					if(lf&(1<<i) && rg&(1<<i)){
						y[i] = a[i]-x[i]+1;
					} else {
						y[i] = a[i]-x[i];
					}
					if(y[i] < 0 || y[i] > ((m-m/2) - (m-m/2)/2)) {
						// printf("   %d %d\n",i, y[i]);
						ok = false;
						break;
					}
				}
				if(!ok) continue;
				int ss = 0;
				for(int i=0;i<n;++i){
					ss *= 6;
					ss += y[i];
				}
				// printf("==>%d %d %d\n", m-m/2, rg, ss);
				if(vis2[m-m/2][rg][ss]){
					printAnswer(lf, s, rg, ss);
					return 0;
				}
			}
		}
	}
	return 0;
}