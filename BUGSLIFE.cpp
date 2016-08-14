#include <bits/stdc++.h>
using namespace std;

#define MAX_N 
int visited[2000];
int value[2000];
vector<int> nbr[2000];

int dfs(int i, int assign){	
	// cout << i << " " << assign << endl;
	if(visited[i]) return 1;
	visited[i] = 1;
	value[i] = assign;
	for(int j = 0; j<nbr[i].size(); j++){
	int child = nbr[i][j];
	int child_assign = 1-value[i];
	if(visited[child] && child_assign != value[child]) return -1;
	int ret = dfs(child, child_assign);
	if(ret == -1) return -1;
	}
	return 1;
}

int main(){
	int t;
	cin >> t;
	for(int tt=1; tt<=t; tt++) {
		int n,e;
		scanf("%d %d",&n,&e);
		for(int i=0;i<n;i++) nbr[i].clear();
		memset(visited, 0, sizeof(visited));
		for(int k=0; k<e; k++) {
			int i,j;
			scanf("%d %d",&i,&j);
			i--; j--;
			nbr[i].push_back(j);
			nbr[j].push_back(i);	
		}
		int flag = 0;
		for(int i=0; i<n; i++){
			if(dfs(i,1) == -1) {
				printf("Scenario #%d:\nSuspicious bugs found!\n",tt);
				flag = 1;
				break;
			}
		}
		if(flag == 0) printf("Scenario #%d:\nNo suspicious bugs found!\n",tt);
	}
}


