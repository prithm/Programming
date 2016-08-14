#include <bits/stdc++.h>
using namespace std;


char inp[50001];
int RA[50001];int SA[50001];
int tempRA[50001];int tempSA[50001];
int c[50001];
long long int ans = 0;
int P[20][50001];

int lcp(int n, int x, int y, int max_steps) {
	if (x == y) return n - x;
	int ret = 0;
	for (int k = max_steps-1; k >= 0 && x < n && y < n; k--){
	if (P[k][x] == P[k][y])
		{x += 1 << k; y += 1 << k; ret += 1 << k;}
	}
	return ret;
}

void countingSortSA(int n, int k) {
	int max_n = max(300, n);
	memset(c, 0, sizeof(c));

	for(int i=0; i<n; i++){
		c[i+k < n ? RA[i+k] : 0]++;
	}

	int sum = 0;
	for(int i=0; i < max_n; i++) {
		int t = c[i]; c[i] = sum; sum += t;
	}

	for(int i=0; i<n; i++){
		tempSA[c[SA[i]+k<n ? RA[SA[i]+k] : 0]++] = SA[i];
	}

	for(int i=0; i<n; i++) SA[i] = tempSA[i];
}

int buildSuffixArray(int n) {
	memset(c, 0, sizeof(c));
	for(int i=0; i<n-1; i++) if (c[inp[i]] == 0) {c[inp[i]] = 1; ans ++;}
	for(int i=0; i<n-1; i++) RA[i] = inp[i]+1;
	RA[n-1] = 0;
	for(int i=0; i<n; i++) SA[i] = i;
	for(int i=0; i<n; i++) P[0][i] = RA[i];
	
	// cout << "SA " ;
	// for(int i=0; i<n; i++) cout << SA[i] << " "; cout << endl;
	// cout << "RA " ;
	// for(int i=0; i<n; i++) cout << RA[i] << " "; cout << endl;
	
	int max_steps = 1;
	for(int k=1; k<n; k*=2,max_steps++){
		countingSortSA(n,k);
		countingSortSA(n,0);

		int r = 0;
		tempRA[SA[0]] = 0;
		for(int i=1; i<n; i++) {
			if ( RA[SA[i]] == RA[SA[i-1]] &&  (SA[i]+k<n ? RA[SA[i]+k] : 0) == (SA[i-1]+k<n? RA[SA[i-1]+k] : 0) ){
				tempRA[SA[i]] =  r;	
			}
			else {
				tempRA[SA[i]] = ++r;
			} 
		}

		for(int i=0; i<n; i++) RA[i] = tempRA[i];
		for(int i=0; i<n; i++) P[max_steps][i] = RA[i];

		// cout << "SA " ;
		// for(int i=0; i<n; i++) cout << SA[i] << " "; cout << endl;
		// cout << "RA " ;
		// for(int i=0; i<n; i++) cout << RA[i] << " "; cout << endl;

		// if(RA[SA[n-1]] == n-1) break;
	}

	return max_steps;
}


int main(){
	int t;
	cin >> t;
	while(t--){
		cin >> inp;
		int n = strlen(inp);
		if (n == 1) {cout << 1 << endl; continue;}
		ans = 0;
		int max_steps = buildSuffixArray(n+1);
		// cout << max_steps << endl;
		// for(int i=0; i<max_steps; i++){
		// 	for(int j=0; j<n+1; j++) cout << P[i][j] << "\t";
		// 	cout << endl;
		// }
		// cout << ans << endl;
		ans = 0;
		for(int i=2; i<n+1; i++){
			int ret = lcp(n, SA[i-1], SA[i], max_steps);
			ans += ret; 
		}
		// ans += 1;
		long long int tot_substrings = (long long)n * (n+1);
		tot_substrings /= 2; 
		cout << tot_substrings - ans << endl;
	}
}