#include <bits/stdc++.h>
using namespace std;

#define MAX_N 2000001

int LPS[MAX_N];
char orig[MAX_N], pattern[MAX_N], a[MAX_N];

void computeLPS(){
	int m = strlen(pattern);
	LPS[0] = 0;

	int i=1;
	int len = 0;
	while(i < m){
		if(pattern[i] == pattern[len]){
			len++;
			LPS[i] = len;
			i++;
		}
		else{
			if(len > 0){
				len = LPS[len-1];
			}
			else{
				LPS[i] = 0;
				i++;
			}
		}
	}
}

int KMP(){
	int n = strlen(orig);
	int m = strlen(pattern);
	int i = 0, j = 0;
	int best = -1;
	int bestind = -1;

	while(i<n){

		if(orig[i] == pattern[j]){
			i++;
			j++;

			if (best < j){
				best = j;
				bestind = i-j;
			} 	

			if(j==m){
				cout << "Found at " << i-j;
				j = LPS[j-1];
			}
		}
		else if(i < n && orig[i]!=pattern[j]){
			if(j > 0)
				j = LPS[j-1];
			else i++;
		}


	}

	return bestind;
}


int main(){
	int n;
	cin >> n;
	cin >> pattern;
	cin >> a;
	strcat(orig,a);
	strcat(orig,a);
	computeLPS();
	cout << KMP() << endl;
}