#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int n;
		scanf("%d", &n);
		// map<string, int> visited;
		queue< pair<string,int> > q;
		q.push(make_pair("1",1%n));
		if(n==1) {cout << 1 << endl; continue;}
		// visited["1"] = 1;
		while(1){
			pair<string, int> temp = q.front();
			q.pop();
			if(temp.second == 0) {cout << temp.first << endl; break;}
			string a = temp.first + '0';
			int rem = (temp.second*10)%n;
			if(rem == 0) {cout << a << endl; break;}
			else { 
				q.push(make_pair(a, (temp.second*10)%n));
			}
			string b = temp.first + '1';
			rem = (temp.second*10 + 1)%n;
			if(rem == 0) {cout << b << endl; break;}
			else { 
				q.push(make_pair(b, (temp.second*10 + 1)%n));
			}
		}
		// q.clear();
	}
}