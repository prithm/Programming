#include <bits/stdc++.h>
using namespace std;

#define MAX_N 10000

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