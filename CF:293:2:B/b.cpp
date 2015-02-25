#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <utility>
#include <set>
#include <string>
using namespace std;


string s, t;
int S[52], T[52];


int main(){

	cin >> s;

	for(int i=0;i<s.size();++i){
		if(s[i]<'a') S[s[i]-'A']++;
		else S[s[i]-'a'+26]++;
	}

	cin >> t;
	for(int i=0;i<t.size();++i){
		if(t[i]<'a') T[t[i]-'A']++;
		else T[t[i]-'a'+26]++;
	}


	int yay = 0;
	int whoops = 0;
	for(int i=0;i<52;++i){
		int x = min(S[i],T[i]);
		yay += x;
		S[i]-=x;
		T[i]-=x;
	}
	for(int i=0;i<26;++i){
		int x = min(S[i]+S[i+26],T[i]+T[i+26]);
		whoops += x;
	}
	printf("%d %d\n",yay,whoops);
	return 0;
}