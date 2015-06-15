#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <new>
using namespace std;


class QuasiBinary {
public:
	QuasiBinary(int n);
	~QuasiBinary(){}
	void generate();
	int getSize();
	void print();
private:
	vector<int> digit;
	vector<int> result;
};

QuasiBinary::QuasiBinary(int n) {
	while (n) {
		digit.push_back(n%10);
		n /= 10;
	}
}

void QuasiBinary::generate() {
	int i = digit.size();
	while (i) {
		int cur = 0;
		for (int k = i-1; k >= 0; --k) {
			cur *= 10;
			cur += (digit[k] ? 1 : 0);
			digit[k] += (digit[k] ? -1 : 0);
		}
		result.push_back(cur);
		while (i > 0 && digit[i-1] == 0) {
			--i;
		}
	}
}

int QuasiBinary::getSize() {
	return result.size();
}

void QuasiBinary::print() {
	for (int i = 0; i < result.size(); ++i) {
		printf("%d ", result[i]);
	}
	printf("\n");
}

int main(){
	int n;
	cin >> n;
	QuasiBinary *qb = new QuasiBinary(n);
	qb->generate();
	printf("%d\n", qb->getSize());
	qb->print();
	delete qb;
	return 0;
}