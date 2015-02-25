#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#include <set>
#include <string>
#include <deque>
using namespace std;


string s;
int N, K;
long long a[200005];
int q[200005];

long long labs(long long x) {
	return x > 0LL ? x : -x;
}

int main(){
	scanf("%d%d",&N,&K);
	for(int i=0;i<N;++i){
		cin >> s;
		if(s[0] == '?') q[i] = 1;
		else {
			if(s[0] == '-') {
				int tmp = 0;
				for(int j=1;j<s.size();++j){
					tmp *= 10;
					tmp += s[j]-'0';
				}
				tmp *= -1;
				a[i] = tmp;
			} else {
				int tmp = 0;
				for(int j=0;j<s.size();++j){
					tmp *= 10;
					tmp += s[j]-'0';
				}
				a[i] = tmp;
			}
		}
	}
	for(int i=N;i<=N+K;++i){
		a[i] = 12345678910;
	}
	vector<int> stack;
	bool ok = true;
	for(int start = 0; start < K; ++start) {
		if(!ok)break;
		long long prev = -12345678910;
		for(int i=start;i<=N+K;i+=K){
			if(!ok)break;
			if(q[i]==1) stack.push_back(i);
			else {
				if(prev >= a[i]) {
					ok = false; 
					break;
				}
				if(a[i] <= 0) {
					long long cnt = 1;
					while(!stack.empty()){
						int j=stack.back();
						stack.pop_back();
						a[j] = a[i]-cnt;
						cnt++;
						if(a[j]<=prev) {
							ok = false;
							break;
						}
					}
				} else if (prev >= 0) {
					for(int j=0;j<stack.size();++j){
						a[stack[j]] = prev+j+1;
						if(a[stack[j]] >= a[i]) {
							ok = false;
							break;
						}
					}
					stack.clear();
				} else if (prev < 0) {
					deque<int> dq;
					int cnt = 1;
					dq.push_back(0);
					int state = 0;
					bool asserted = false;
					for(int j=1;j<stack.size();++j){
						if(!asserted) {
							if(state == 0) {
								if(cnt >= a[i]) {
									asserted = true;
									state = 1;
									cnt *= -1;
									// if(cnt <= prev) {
									// 	ok = false;
									// 	break;
									// } else {
									// 	dq.push_front(cnt);
									// 	cnt *= -1;
									// 	cnt++;
									// }
								} else {
									dq.push_back(cnt);
									cnt *= -1;
									state = 1;
								}
							} else {
								if(cnt <= prev) {
									asserted = true;
									state = 0;
									cnt--;
									cnt *= -1;
									// if(cnt <= a[i]) {
									// 	ok = false;
									// 	break;
									// } else {
									// 	dq.push_back(cnt);
									// 	cnt++;
									// 	cnt *= -1;
									// }
								} else {
									dq.push_front(cnt);
									cnt--;
									cnt *= -1;
									state = 0;
								}
							}
						}
						if(asserted) {
							if(state == 0) {
								if(cnt >= a[i]) {
									ok = false; break;
								}
								dq.push_back(cnt);
								cnt ++;
							} else {
								if(cnt <= prev) {
									ok = false; break;
								}
								dq.push_front(cnt);
								cnt --;
							}
						}
					}
					for(int j=0;j<stack.size();++j){
						a[stack[j]] = dq[j];
					}
					stack.clear();
				}
				prev = a[i];
				if(!ok)break;
			}
			if(i >= N) break;
		}
	}
	if(!ok) {
		printf("Incorrect sequence\n");
	}
	else {
		for(int i=0;i<N;++i){
			if(i!=0)printf(" ");
			printf("%d",(int)a[i]);
		}
		printf("\n");
	}
	return 0;
}