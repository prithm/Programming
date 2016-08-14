#include <bits/stdc++.h>
using namespace std;

#define MAX_N 30001
#define GI ({int y;scanf("%d",&y);y;})
#define make_pair mp

typedef pair<int,int> PII;
typedef pair<PII,int> PIII;
int inp[MAX_N+1];
PIII query[200010];
int ans[200010];

map<int, int> m;

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
	int n = GI;
	for(int i=1; i<=n; i++) inp[i] = GI;
	int q = GI;
	for(int i=0; i<q; i++){
		int l = GI; int r = GI;
		query[i] = PIII( PII(r,l), i );
	}
	sort(query,query+q);
	memset(tree, 0, sizeof(tree));

	// for(int i=0; i<q; i++) cout << "(" << query[i].first << "," << query[i].second << "), "; cout << endl;
	int j = 0;
	for(int i=1; j<q && i<=n; i++) {
		if(m.count(inp[i]) != 0) {
			int prev_occur = m[inp[i]];
			update(prev_occur, -1, n);
		}
		update(i, 1, n);
		m[inp[i]] = i;
		for(;j<q && query[j].first.first == i; j++) {
			int l = query[j].first.second; int r = query[j].first.first;
			ans[query[j].second] = cum_fre(r) - cum_fre(l-1);
		}
	}

	for(int i=0; i<q; i++) printf("%d\n", ans[i]);
}

