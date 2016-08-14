#include <bits/stdc++.h>
using namespace std;

#define MAX_N 10000
int visited[MAX_N];
int value[MAX_N];
vector<int> nbr[MAX_N];
int ans = 0;

int dfs(int i){	
	int m1 = 0, m2= 0;
	for(int j = 0; j<nbr[i].size(); j++){
		int child = nbr[i][j];
		if(visited[child] == 0) {
			visited[child] = 1;
			int m = dfs(child);
			if(m >= m1) {
				m2 = m1;
				m1 = m;
			}
			else if(m > m2) m2 = m;
		}
	}
	ans = max(ans, m1+m2);
	return 1+m1;
}

int main(){

	int n;
	scanf("%d",&n);
	memset(visited, 0 , sizeof(visited));
	for(int k=0; k<n-1; k++) {
		int i,j;
		scanf("%d %d",&i,&j);
		i--; j--;
		nbr[i].push_back(j);
		nbr[j].push_back(i);	
	}
	visited[0] = 1;
	dfs(0);
	cout << ans << endl;
}


