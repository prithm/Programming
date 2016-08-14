#include <bits/stdc++.h>
using namespace std;

int visited[101];
int value[101];
pair<int,int> inp[101];

int dfs(int i, int assign){
	if(visited[i]) return 1;
	visited[i] = 1;
	value[i] = assign;
	int child = inp[i].first;
	int child_assign = assign == 1? inp[i].second : 1-inp[i].second;
	if(visited[child] && child_assign != value[child]) return -1;
	return dfs(child, child_assign);
}

int main() {
	while(1){
		int n;
		cin >> n;
		if(n == 0) return 0;
		memset(visited, 0, sizeof(visited));
		for(int i=0; i<n; i++){
			int j; string str;
			cin >> j >> str;
			// cout << j << " " << str << endl;
			j--;
			if(str == "true")
				inp[i] = make_pair(j,1);
			else inp[i] = make_pair(j,0);
		}

		int flag = 0;
		for(int i=0; i<n; i++){
			if(dfs(i, 1) == -1){
				memset(visited, 0, sizeof(visited));
				if(dfs(i,0) == -1){
					cout << "PARADOX" << endl;
					flag = 1;
					break;
				}
			}
		}

		if(flag == 0) cout << "NOT PARADOX" << endl;
	}
}