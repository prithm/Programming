#include <bits/stdc++.h>
using namespace std;

int a[100000];

bool p(int n, int c, int diff){
	int set = 1;
	int last = a[0];
	for(int i=1;i<n;i++){
		if (a[i]-last >= diff){
			set += 1;
			last = a[i];
		}
		if(set >= c) break;
	}
	if(set >= c) return true;
	return false;
}

int solve(int n,int c){
	int low = 1;
	int high = a[n-1]-a[0];
	if (c==2) return high;
	// int u;
	while(low < high){
		// cout << low << " " <<  high << endl;
		// cin >> u;
		int mid = low + (high - low)/2;
		if(p(n,c,mid)) low = mid;
		else high = mid-1;
		if (low == high-1) return p(n,c,high) ? high : low;
	}

	return high;
}

int main() {
	int t;
	int n,c;
	cin >> t;
	while(t--){
		cin >> n >> c;
		for(int i=0; i<n; i++) cin >> a[i];
		sort(a,a+n);
		cout << solve(n,c) << endl;
	}
} 