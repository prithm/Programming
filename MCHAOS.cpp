#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100001
#define GI ({int y;scanf("%d",&y);y;})
#define make_pair mp

typedef long long int ll;
typedef pair<int,int> PII;
typedef pair<PII,int> PIII;
typedef pair<ll,ll> PLL;
typedef pair<PLL,ll> PLLL;

char temp[10];
PLL inp[MAX_N];
ll a[MAX_N];
ll b[MAX_N];

ll invcount = 0;

void myMerge(ll *a, int l, int r){
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

void myMergesort(ll*a, int l, int r){
	if (l==r) return;
	int mid = (l+r)/2;
	myMergesort(a,l,mid);
	myMergesort(a,mid+1,r);
	myMerge(a,l,r);
}


int main() {
	int n = GI;
	for(int j=0; j<n; j++) {
		scanf("%s", temp);
		int l = strlen(temp);
		ll hash = 0;
		for(int i=0; i<l; i++) hash = hash * 27 + (temp[i] - 'a') + 1;
		for(int i=l; i<10; i++) hash *= 27;

		ll rev_hash = 0;
		for(int i=l-1; i>=0; i--) rev_hash = rev_hash * 27 + (temp[i] - 'a') + 1;
		for(int i=l; i<10; i++) rev_hash *= 27;
		
		inp[j] = PLL(hash, rev_hash); 		
	}

	sort(inp, inp+n);
	invcount = 0;
	for(int i=0; i<n; i++) {
		a[i] = inp[i].second;
	}

	myMergesort(a,0,n-1);

	printf("%lld\n",invcount);
}