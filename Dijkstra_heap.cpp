#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define MAX_N 10000

int visited[MAX_N];
long long int dist[MAX_N];
vector< pair<int,int> > nbr[MAX_N];
map<string, int> city_ind;
char temp[20], temp2[20];

int main(){
	int t;
	scanf("%d",&t);
	while(t--) {
		int n;
		scanf("%d",&n);
		for(int i=0;i<n;i++)nbr[i].clear();
		
		for(int i=0; i<n; i++) {
			scanf("%s",temp);
			city_ind[temp] = i;
			int p;
			scanf("%d",&p);
			for(int j=0; j<p; j++) {
				int id,c;
				scanf("%d %d",&id,&c);
				id--;
				nbr[i].pb(mp(id,c));
			}
		}

		int r;
		scanf("%d",&r);
		for(int k=0; k<r; k++) {
			scanf("%s %s",temp,temp2);
			int source = city_ind[temp];
			int dest = city_ind[temp2];

			// cout << source << " " << dest << endl;
			memset(visited,0,sizeof(visited));
			memset(dist,-1,sizeof(dist));
			
			priority_queue< pair<long long int, int>, vector< pair<long long int, int> > > q;
			q.push(mp(0,source));
			int marked = 0;
			dist[source] = 0;

			while(marked < n) {
				pair<long long int, int> min_vertex = q.top();
				q.pop();
				int min_ind = min_vertex.second;
				if(visited[min_ind] == 1) continue;
				visited[min_ind] = 1;
				if(min_ind == dest) break;
				marked++;
				for(int i=0; i<nbr[min_ind].size(); i++){
					int j = nbr[min_ind][i].first;
					int d = nbr[min_ind][i].second;
					if(visited[j]==0 && (dist[j] < 0 || dist[j] > dist[min_ind] + d)) {
						dist[j] = dist[min_ind] + d;
						q.push(mp(-dist[j],j));
					}
				}
			}
			if(dist[dest] >= 0) printf("%lld\n",dist[dest]);
			else printf("NO\n");

		}
	}
}
