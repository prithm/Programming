#include <bits/stdc++.h>
using namespace std;

#define MAX_N 1000001

int LPS[MAX_N];
char orig[MAX_N], pattern[MAX_N];

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

void KMP(){
	int n = strlen(orig);
	int m = strlen(pattern);
	int i = 0, j = 0;

	while(i<n){

		if(orig[i] == pattern[j]){
			i++;
			j++;	
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
}


int main(){
	cin >> orig;
	cin >> pattern;
	computeLPS();
	KMP();
}