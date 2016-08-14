#include <bits/stdc++.h>
using namespace std;

#define mp make_pair 

int visited[8][8];
char start[3], dest[3];

int move_i[8] = {-2,+2,-1,+1,-2,+2,-1,+1};
int move_j[8] = {-1,+1,-2,+2,+1,-1,+2,-2};

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		scanf("%s %s",start,dest);
		
		int start_i = start[0] - 'a';
		int start_j = start[1]-'0';
		int dest_i = dest[0] - 'a';
		int dest_j = dest[1]-'0';	
		start_j--; dest_j--;

		if(start_i == dest_i && start_j == dest_j) {cout << "0" << endl; continue;}
		queue< pair<int,int> > q;
		memset(visited, 0, sizeof(visited));
		visited[start_i][start_j] = 1;
		int depth = 0;
		q.push(mp(start_i, start_j));
		int prev_size = q.size();
		// cout << start_i << " " << start_j << " " << dest_i << " " << dest_j << endl;
		int flag = 0;
		while(1){
			pair<int, int> temp = q.front();
			q.pop();
			for(int i=0;i<8;i++){
				int next_i = move_i[i]+temp.first;
				int next_j = move_j[i]+temp.second;
				if(next_i >=0 && next_i < 8 && next_j >=0 && next_j < 8){
					if (next_i == dest_i && next_j == dest_j) {cout << depth+1 << endl; flag=1; break;}
					if(visited[next_i][next_j] == 0) {
						visited[next_i][next_j] = 1;
						q.push(mp(next_i,next_j));
					}
				}
			}
			if(flag == 1) break;
			prev_size--;
			if(prev_size == 0) {depth++; prev_size = q.size();} 
		}
	}
}