#include <bits/stdc++.h>
using namespace std;

#define MAX_N 30000
#define ll long long int

int a[MAX_N];
int b[MAX_N];
int cnt[MAX_N];
ll invcount = 0;

void myMerge(int *a, int l, int r){
	if(l==r) return;
	for(int i=l; i<=r; i++) b[i] = a[i];
	int mid=(l+r)/2;
	int p1=l,p2=mid+1;
	int k=l;
	while(p1<=mid && p2<=r){
		if(b[p1] <= b[p2]) {a[k++] = b[p1++];}
		else {invcount += mid-p1+1; a[k++] = b[p2++];} 
	}
	if(p1<=mid)
		while(p1<=mid) a[k++] = b[p1++];
	else while(p2<=r) a[k++] = b[p2++];
}

void myMergesort(int*a, int l, int r){
	if (l==r) return;
	int mid = (l+r)/2;
	myMergesort(a,l,mid);
	myMergesort(a,mid+1,r);
	myMerge(a,l,r);
}

char temp[30];

int main() {
	int t;
	cin >> t;
	while(t--) {
		int n;
		scanf("%d",&n);
		map<string, queue<int> > m;
		for(int i=0; i<n; i++){ 
			scanf("%s", temp);
			m[temp].push(i);
		}
		for(int i=0; i<n; i++){
			scanf("%s", temp);
			a[i] = m[temp].front();
			m[temp].pop();
		}	
		invcount = 0;
		myMergesort(a,0,n-1);
		printf("%lld\n", invcount);
	}
}	