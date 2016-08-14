#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100001
#define GI ({int y;scanf("%d",&y);y;})
#define make_pair mp

typedef pair<int,int> PII;
typedef pair<PII,int> PIII;

PIII inp[MAX_N];

int main(){
	int t = GI;
	while(t--) {
		int n = GI;
		for(int i=0; i<n; i++){
			int x,y,z;
			x = GI; y = GI; z = GI;
			inp[i] = PIII( PII(x,y), z );
		}
		sort(inp,inp+n);

		set<PII> S;
		int ans = 0;				
		for(int i=0; i<n; i++) {
			int x = inp[i].first.first, y = inp[i].first.second, z = inp[i].second;
			S.insert(PII(y,z));
			
			int flag;
			flag = 0;
			set<PII>::iterator it = S.find(PII(y,z));	
			while( it != S.begin() ){
				it--;
				if( it->second <= z ) {
					flag = 1;
				}
			}
			if(flag == 0) ans++;
		}
		printf("%d\n",ans);
	}
}