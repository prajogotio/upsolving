#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
using namespace std;

string s;
long long cnt[2][2];

int main(){
	cin >> s;
	int N = s.size();
	long long odd=0,even=0;
	int cur = 0, next;
	for(int i=0;i<N;++i){
		next = (cur+1)%2;
		odd += cnt[s[i]-'0'][cur];
		even += cnt[s[i]-'0'][next];
		odd++;
		cnt[s[i]-'0'][cur]++;
		cur = next;
	}
	cout << even << " " << odd << endl;
	return 0;
}