#include <bits/stdc++.h>
using namespace std;

#define MAX_N 20001
#define GI ({int y;scanf("%d",&y);y;})
#define make_pair mp

typedef pair<int,int> PII;
typedef pair<PII,int> PIII;
int inp[MAX_N+1];
int ans[MAX_N+1];

long long int tree[MAX_N+1];

void update(int ind, int val, int max_val){
	for(int i=ind; i<=max_val; i += (i & -i)) {
		tree[i] += val;
	}
}

int cum_fre(int ind) {
	int sum = 0;
	for(int i=ind; i>0; i-= (i & -i)) {
		sum += tree[i];
	}
	return sum;
}

int main(){
	int t = GI;
	while(t--) {
		int n = GI;
		memset(ans,0,sizeof(ans));
		memset(tree,0,sizeof(tree));
		
		for(int i=1; i<=n; i++) update(i,1,n);

		int rmv = 1;
		int prev = 0;
		int i;
		for(i=0; i<n; i++){
			rmv = (rmv + i + 1)%(n-i);
			if(rmv == 0) rmv = n-i;

			int s = 1, e = n;
			while(s<e){
				if(s == e-1) {if(cum_fre(s) < rmv) s = e; break;}
				int mid = (s+e)/2;
				if(cum_fre(mid)>=rmv) e = mid;
				else s = mid+1;
			}

			ans[s] = i+1; update(s, -1, n);
		}

		// for(int j=0; i<n && j<n; j++)
		// 	if(inp[(prev+j)%n] == 0) {
		// 		ans[(prev+j)%n] = i+1;
		// 		inp[(prev+j)%n] = 1;
		// 		i++;
		// 	}

		for(int i=1; i<=n; i++) printf("%d ", ans[i]);
		printf("\n");
	}
}


