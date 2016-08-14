#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100000
#define ll long long int

ll tree1[MAX_N+1], tree2[MAX_N+1];

void update_util(ll* tree, int ind, ll val, int max_val){
	for(int i=ind; i<=max_val; i += (i & -i)) {
		tree[i] += val;
	}
}

void update(int a, int b, ll val, int max_val) {
	update_util(tree1, a, val, max_val);
	update_util(tree1, b + 1, -val, max_val);
	update_util(tree2, a, val * (a-1), max_val);
	update_util(tree2, b + 1, -val * b, max_val);
}

ll query(ll* tree, int ind) {
	ll sum = 0;
	for(int i=ind; i>0; i-= (i & -i)) {
		sum += tree[i];
	}
	return sum;
}

ll query_from_start_to(int ind) {
	return query(tree1, ind) * ind - query(tree2, ind);
}

ll query_range(int a, int b) {
	return query_from_start_to(b) - query_from_start_to(a-1);
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--) {
		int n,c;
		scanf("%d %d", &n, &c);
		memset(tree1, 0, sizeof(tree1));
		memset(tree2, 0, sizeof(tree2));
		while(c--) {
			int flag;
			scanf("%d", &flag);
			if(flag == 0) {
				int a,b;
				ll val;
				scanf("%d %d %lld", &a, &b, &val);
				update(a,b,val,n);
			}
			else if(flag == 1) {
				int a,b;
				scanf("%d %d", &a, &b);
				printf("%lld\n",query_range(a,b));
			}
		}
	}
}
