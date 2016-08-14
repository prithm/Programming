#include <bits/stdc++.h>
using namespace std;

#define MAX_N 500010

string a,b, inp;
int RA[MAX_N]; int SA[MAX_N];
int tempRA[MAX_N]; int tempSA[MAX_N];
int c[MAX_N];
int P[20][MAX_N];
int mark[MAX_N];
int LCP[MAX_N];

int lcp(int n, int x, int y, int max_steps) {
	if (x == y) return n - x;
	int ret = 0;
	for (int k = max_steps-1; k >= 0 && x < n && y < n; k--){
	if (P[k][x] == P[k][y])
		{x += 1 << k; y += 1 << k; ret = (ret + 1 << k);}
	}
	return ret;
}

void countingSortSA(int n, int k) {
	int max_ind = max(300, n);
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

	int n;
	cin >> a;
	cin >> b;
	inp = a + "#" + b;

	n = inp.length();
	// for (int i=0; i<n; i++) cout << inp[i] << " "; cout << endl;
		 
	int max_steps = buildSuffixArray(n+1);
	// cout << max_steps << endl;
	// for(int i=0; i<max_steps; i++){
	// 	for(int j=0; j<n+1; j++) cout << P[i][j] << "\t";
	// 	cout << endl;
	// }
	// cout << ans << endl;
	
	// for (int i=0; i<n+1; i++) cout << SA[i] << " "; cout << endl;
	int ans = 0;	
	int m = a.length();
	memset(LCP,0,sizeof(LCP));
	set<string> all_lcs;

	for(int i=2; i<n+1; i++){
		if( (SA[i-1] < m && SA[i] > m) || (SA[i] < m && SA[i-1] > m) ){
			LCP[i-2] = lcp(n, SA[i-1], SA[i], max_steps);
		}
		ans = max(LCP[i-2],ans);		
	}

	if(ans == 0) cout << ans << endl;
	else{
		for(int i=0;i<n-1;i++) 
			if(LCP[i] == ans) {
				string temp;
				int j = SA[i+1], k = SA[i+2];
				while(j<n && k<n && inp[j]==inp[k]){
					temp += inp[j]; j++; k++;
				}
				all_lcs.insert(temp);
			}
 
		string to_find=b.substr(0,ans);
		if((all_lcs.find(to_find))!=all_lcs.end()){
		   	cout << to_find << endl << ans << endl;
		   	return 0;
		}
		
		for(int i=1;i<b.length()-ans; i++) {  
			to_find.erase(to_find.begin());
			to_find = to_find + b[i+ans-1]; 
			
			if((all_lcs.find(to_find))!=all_lcs.end()){
				cout << to_find << endl << ans << endl;
			  	break;
			} 
		}
   		// for(int i = ind; i<ind+ans; i++) cout << inp[i]; cout << endl; cout << ans << endl;
	}
}