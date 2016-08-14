#include <bits/stdc++.h>
using namespace std;

#define MAX_N 2000001
#define MOD 1000000009

int inp[MAX_N];
int a[MAX_N];
int RA[MAX_N]; int SA[MAX_N];
int tempRA[MAX_N]; int tempSA[MAX_N];
int c[MAX_N];
long long int ans = 0;
int P[20][MAX_N];
// int max_num;

long long int lcp(int n, int x, int y, int max_steps) {
	if (x == y) return n - x;
	long long int ret = 0;
	for (int k = max_steps-1; k >= 0 && x < n && y < n; k--){
	if (P[k][x] == P[k][y])
		{x += 1 << k; y += 1 << k; ret = (ret + 1 << k)%MOD;}
	}
	return ret;
}

void countingSortSA(int n, int k) {
	int max_ind = max(210, n);
	memset(c, 0, sizeof(c));

	for(int i=0; i<n; i++){
		c[i+k < n ? RA[i+k] : 0]++;
	}

	long long int sum = 0;
	for(int i=0; i < max_ind; i++) {
		int t = c[i]; c[i] = sum; sum += t;
	}

	for(int i=0; i<n; i++){
		tempSA[c[SA[i]+k<n ? RA[SA[i]+k] : 0]++] = SA[i];
	}

	for(int i=0; i<n; i++) SA[i] = tempSA[i];
}

int buildSuffixArray(int n) {
	// cout << "In Sufix Array" << endl;
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

		if(RA[SA[n-1]] == n-1) break;
	}

	return max_steps;
}


int main(){
	int t;
	cin >> t;
	while(t--){
		int n;
		cin >> n;
		for (int i=0; i<n; i++)
			cin >> a[i];
		if (n == 1) {cout << 0 << endl; continue;}
		if (n == 1) {cout << 1 << endl; continue;}
		
		int minn = 500000;
		for (int i=1; i<n; i++){
			inp[i-1] = a[i]-a[i-1];
			minn = min(minn,inp[i-1]);
		}

		// max_num = -1;
		for (int i=0; i<n-1; i++){
			inp[i] = inp[i] - minn;
			// max_num = max(inp[i], max_num);
		}

		// for (int i=0; i<n-1; i++) cout << inp[i] << " "; cout << endl;
			 
		int max_steps = buildSuffixArray(n);
		// cout << max_steps << endl;
		// for(int i=0; i<max_steps; i++){
		// 	for(int j=0; j<n+1; j++) cout << P[i][j] << "\t";
		// 	cout << endl;
		// }
		// cout << ans << endl;
		
		// for (int i=0; i<n; i++) cout << SA[i] << " "; cout << endl;

		ans = 0;
		for(int i=2; i<n; i++){
			long long int ret = lcp(n, SA[i-1], SA[i], max_steps);
			ans = (ans + ret)%MOD; 
		}
		// ans += 1;
		// n++;
		n-=1;
		long long int tot_substrings = 0;
		for(int i=1; i<=n; i++) tot_substrings = (tot_substrings + i)%MOD;
		long long int dist_tot_substrings = (tot_substrings - ans)%MOD;
		if(dist_tot_substrings < 0) dist_tot_substrings += MOD;
		cout << dist_tot_substrings << endl;
	}
}