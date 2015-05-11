#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

/**
	Cool!
	given xWa + yWb <= C,
	maximize xHa + yHb.
	1.	if either Wa or Wb > sqrt C, iterate through those sqrt C choices
	2.	otherwise Wa & Wb < sqrt C.
		WLOG Ha/Wa < Hb/Wb.
		suppose x > Wb.
		then xWa + yWb <= C
		=>   (x-Wb)Wa + WbWa + yWb <= C
		=>   (x-Wb)Wa + (y+Wa)Wb <= C
		and  (x-Wb)Ha + (y+Wa)Hb = xHa + yHb + HbWa - WbHa > xHa + yHb
		hence if x > Wb, there is more optimal arrangement such that x < Wb.
		So we only need to iterate through all possibilities where x < Wb,
		since Wb < sqrt C, the choices is less than sqrt C
*/

int main(){
	long long C,Ha,Hb,Wa,Wb;
	cin >> C >> Ha >> Hb >> Wa >> Wb;
	if (Wa*Wa >= C || Wb*Wb >= C){
		if(Wa > Wb) {
			swap(Wa,Wb);
			swap(Ha,Hb);
		}
		long long ans = -1;
		for(long long y=0;y*Wb<=C;++y){
			long long x = (C - y*Wb)/Wa;
			ans = max(x*Ha+y*Hb, ans);
		}
		cout << ans << endl;
	} else {
		if(Ha * Wb > Hb * Wa) {
			swap(Wa,Wb);
			swap(Ha,Hb);
		}
		long long ans = -1;
		for(long long x=0; x<=Wb;++x){
			long long y = (C - x*Wa)/Wb;
			ans = max(x*Ha+y*Hb, ans);
		}
		cout << ans << endl;
	}
	return 0;
}
