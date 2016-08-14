#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair
#define MAX_N 10000

int visited[MAX_N];
long long int dist[MAX_N];
vector< pair<int,int> > nbr[MAX_N];

int main() {
	int t;
	scanf("%d",&t);
	while(t--){
		int n,e;
		scanf("%d %d",&n,&e);
		memset(visited,0,sizeof(visited));
		memset(dist,-1,sizeof(dist));
		for(int i=0;i<n;i++)nbr[i].clear();
		for(int k=0; k<e; k++){
			int i,j,c;
			scanf("%d %d %d",&i,&j,&c);
			i--; j--;
			nbr[i].pb(mp(j,c));
		}
		int source, dest;
		scanf("%d %d",&source,&dest);
		source--; dest--;

		dist[source] = 0;
		int marked = 0;
		while(marked < n) {
			int minn = -1, min_ind = -1;
			for(int i=0; i<n; i++){
				if(visited[i] == 0 && dist[i] >= 0)
					if(minn == -1 || minn > dist[i]) { minn = dist[i]; min_ind = i;}
			}
			visited[min_ind] = 1;
			if(min_ind == dest) break;
			marked++;
			for(int i=0; i<nbr[min_ind].size(); i++){
				int j = nbr[min_ind][i].first;
				int d = nbr[min_ind][i].second;
				if(visited[j] == 0 && (dist[j] < 0 || dist[j] > dist[min_ind] + d))
					dist[j] = dist[min_ind] + d;
			}
		}
		if(dist[dest] >= 0) printf("%lld\n",dist[dest]);
		else printf("NO\n");
	}
}