#include <bits/stdc++.h>
using namespace std;

#define MAX_N 250001

char a[MAX_N], b[MAX_N];
int hash_present[35000000];
int next[35000000]; 
int start_ind[35000000]; 
int cur_loc = 0;
// int step = 0;
long long int MOD = 34369934;
long long int D = 9584612342;

void insert_hash(int ind, int hash){
	
	// if(visited[hash] != step){
	// 	visited[hash] = step;
	// 	hash_present[hash] = -1;
	// }

	int prev = hash_present[hash];
	hash_present[hash] = cur_loc;
	next[cur_loc] = prev;
	start_ind[cur_loc] = ind;
	cur_loc++;
	// if(ind == 7) cout << "hash:" << ind << " " << hash << " " << hash_present[hash] << endl; 
}

bool matches(int ind, int hash, int len){
	// if(ind==0 && len==2){ 
	// 	cout << "Entered matches" << endl;
	// 	cout << hash << endl;
	// 	cout << hash_present[hash] << endl;
	// 	cout << "matches" << endl;
	// }

	// if (visited[hash] != step) return false;

	for(int i=hash_present[hash]; i!=-1; i=next[i]){
		int start = start_ind[i];
		int flag = 0;
		for(int j=0; j < len; j++){
			if(a[start + j] != b[ind + j]){
				flag = 1;
				break;
			}
		}
		if (flag == 0) return true;
	}
	return false;
} 

int p(int len){

	// step++;
	cur_loc = 0;
	memset(hash_present,-1,sizeof(hash_present));	

	if(len == 0) return -1;

	long long int a_hash = 0;
	long long int b_hash = 0;
	long long int h = 1;
	int a_len = strlen(a);
	int b_len = strlen(b);

	for(int i=0; i<len; i++){
		a_hash = ( (a_hash*D) + (a[i]) )%MOD;
		b_hash = ( (b_hash*D) + (b[i]) )%MOD;
		h = (h*D)%MOD;
	}

	h = (MOD - h) % MOD;

	insert_hash(0, a_hash);
	for(int i=0; i < a_len-len; i++){
		a_hash = (a_hash * D + a[i+len] + h*a[i])%MOD;
		insert_hash(i+1, a_hash);
	}

	if (matches(0, b_hash, len)){
			return 0;
	}

	for(int i=0; i < b_len-len; i++){
		b_hash = (b_hash * D + b[i+len] + h*b[i])%MOD;
		if (matches(i+1, b_hash, len)){
				return i+1;
		}
	}

	return -1;
}

// int binary_search(){

// 	return low;
// }


int main() {
	scanf("%s %s", a, b);

	int l1 = strlen(a);
	int l2 = strlen(b);

	int low = 0;
	int high = l2;
	int ans_ind;
	while(low < high){
		// cout << low << " " <<  high << endl;
		if (low == high-1) {
			ans_ind =  p(high);
			if(ans_ind >= 0) low = high;
		}
		// cin >> u;
		int mid = (low + high + 1) >> 1;
		ans_ind = p(mid);
		// cout << mid << " " << ans_ind << endl;
		if(ans_ind >= 0) low = mid;
		else high = mid-1;
	}

	if(low == 0) cout << "0" << endl;
	else{
		int ans_ind = p(low);
		b[ans_ind + low] = 0;
		printf("%s\n",b+ans_ind);
		printf("%d\n",low);
	}
}
