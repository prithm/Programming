#include <bits/stdc++.h>
using namespace std;

#define MAXX 10000000

int dist[101][101];

int main() {
	while(1){
		int n;
		cin >> n;
		if(n == 0) return 0;
		for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			dist[i][j] = MAXX;
		
		for(int i=0; i<n; i++){
			int j; string str;
			cin >> j >> str;
			// cout << j << " " << str << endl;
			j--;
			if(str == "true")
				dist[i][j] = 2;
			else dist[i][j] = 1;
		}

		for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(dist[i][j]>dist[i][k]+dist[k][j])
				dist[i][j] = dist[i][k] + dist[k][j];

		int flag = 0;
		for(int i=0; i<n; i++)
			if(dist[i][i] < MAXX && dist[i][i]%2 == 1){
				cout << "PARADOX" << endl;
				flag=1;
				break;
			}

		if(flag == 0){
			cout << "NOT PARADOX" << endl;
		}
	}
}


// #include <bits/stdc++.h>
// using namespace std;
 
// #define MX 10000000
 
// int main() {
// 	// your code goes here
// 	int T;
// 	while(1)
// 	{
// 		int N,i,j,k;
// 		cin>>N;	
// 		if(N==0)
// 			return 0;
// 		int dis[N+1][N+1];
// 		memset(dis,0,sizeof(dis));
// 		for(i=0; i<=N ; i++)
// 			for(j=0 ; j<=N ; j++)
// 				dis[i][j] = MX;
 
// 		for(i=1 ; i<=N ; i++)
// 		{
// 			int x;
// 			string str;
// 			cin>>x>>str;
// 			if(str == "true")
// 				dis[i][x] = 2;
// 			else
// 				dis[i][x] = 1;
// 		}
 
// 		for(k=1;k<=N;k++)
// 		{
// 			for(i=1;i<=N;i++)
// 			{	
// 				for(j=1;j<=N;j++)
// 				{
// 					if(dis[i][j]>dis[i][k]+dis[k][j])
// 					{
// 						dis[i][j]=dis[i][k]+dis[k][j];
// 					}
// 				}
// 			}
// 		}
 
// 		int temp=0;
// 		for(i=1 ; i<=N ; i++)
// 		{
// 			if( dis[i][i] < MX/ 2 && dis[i][i] % 2 == 1)
// 			{
// 				cout<<"PARADOX"<<endl;
// 				temp = 1;
// 				break;
// 			}
 
// 		}
// 		if(temp == 0)
// 		{
// 			cout<<"NOT PARADOX"<<endl;
// 		}
// 	}
// 	return 0;
// }