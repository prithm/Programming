#include <bits/stdc++.h>
using namespace std;

#define MAX_N 10000
#define MOD 101
#define D 256

char orig[MAX_N], pattern[MAX_N];

void RabinKarp(){

	int orig_hash = 0;
	int pattern_hash = 0;
	int h = 1;
	int n = strlen(orig);
	int m = strlen(pattern);

	for(int i=0; i<m; i++){
		orig_hash = ( (orig_hash*D)%MOD + (orig[i]) )%MOD;
		pattern_hash = ( (pattern_hash*D)%MOD + (pattern[i]) )%MOD;
	}

	for(int i=0; i<m-1; i++) h = (h*D)%MOD;

	for(int i=0; i <= n-m; i++){
		if (orig_hash == pattern_hash){
			int j = 0;
			for(j=0; j<m; j++){
				if(orig[i+j]!=pattern[j])break;
			}
			if(j==m) cout << "Pattern found at " << i << endl;
		}

		if(i < n-m){
			orig_hash = (orig_hash - ((orig[i])*h)%MOD)%MOD;
			if (orig_hash < 0) orig_hash += MOD;
			orig_hash = ( (orig_hash*D)%MOD + (orig[i+m]) )%MOD;
		}
	}

}

int main() {
	cin >> orig;
	cin >> pattern;
	RabinKarp();
}