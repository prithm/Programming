#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100001
#define GI ({int y;scanf("%d",&y);y;})
#define make_pair mp

typedef pair<int,int> PII;
typedef pair<PII,int> PIII;

int reverse(int n) {
	int p = 0;
	while(n > 0) {
		p = p*10 + (n%10);
		n /= 10;
	}
	return p;
}

int main() {
	int t = GI;
	while(t--) {
		int a = GI; int b = GI;
		printf("%d\n",reverse(reverse(a) + reverse(b)));
	}
}