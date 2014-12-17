#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#include <cmath>
using namespace std;

double EPS = 1e-12;

double PI = 2*acos(0);
vector<double> angles;
int N;

int bsearch(double a) {
	int lo=0, hi = N-1, mid;
	while(lo <= hi) {
		mid = (lo+hi)/2;
		if(angles[mid] < a) {
			lo = mid +1;
		} else {
			hi = mid -1;
		}
	}
	return lo;
}

class TrianglesContainOrigin {
public:
	long long count(vector<int> x, vector<int> y) {
		N = x.size();
		angles.clear();
		for(int i=0;i<N;++i){
			if(x[i] == 0) {
				if(y[i] > 0) angles.push_back(PI/2.0);
				else angles.push_back(3.0 * PI / 2.0);
				continue;
			} else if (y[i] == 0) {
				if(x[i] > 0) angles.push_back(0);
				else angles.push_back(PI);
				continue;
			}
			double p = 1.0 * y[i] / x[i];
			double angle = atan(p);
			if(x[i] > 0 && y[i] > 0) {
				//first quadrant
			} else if(x[i] < 0 && y[i] > 0) {
				//second
				angle += PI;
			} else if(x[i] < 0 && y[i] < 0) {
				//third
				angle += PI;
			} else if(x[i] > 0 && y[i] < 0) {
				//fourth
				angle += 2*PI;
			} 
			angles.push_back(angle);
		}
		sort(angles.begin(), angles.end());
		long long ans = 0;
		//for(int i=0;i<N;++i)printf("\n%lf", angles[i]);
		for(int i=0;i<N;++i){
			for(int j=i+1;j<N;++j){
				if(angles[i] < PI) {
					if(angles[j] >= PI) {
						break;
					}
					double alpha = angles[i] + PI;
					double beta = angles[j] + PI;
					int L = bsearch(alpha);
					int R = bsearch(beta) - 1;
					//printf("\n%d %d", L, R);
					if(L>R)continue;
					ans += R - L + 1;
				} else {
					double alpha = angles[i] - PI;
					double beta = angles[j] - PI;
					int L = bsearch(alpha);
					int R = bsearch(beta) - 1;
					if(L>R) continue;
					ans += R - L + 1;
				}
			}
		}
		return ans;
	}
};