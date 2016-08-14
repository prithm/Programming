#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100001

int tree[MAX_N];

void update(int pos,int val,int max_val)
{
    while(pos <= max_val)
    {
        tree[pos] = min(tree[pos] , val);
        pos += (pos & -pos);
    }
}

int read(int pos)
{
    int check = INT_MAX;
    while(pos)
    {
        check = min(tree[pos] , check);
        pos -= (pos & -pos);
    }
    return check;
}

struct data
{
    int first,second,third;
};

bool cmp(const data &a , const data &b)
{
    return a.first == b.first ? (a.second == b.second ? a.third < b.third : a.second < b.second ) : a.first < b.first;
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n;
        scanf("%d",&n);
        data inp[n];
        for(int i=0;i<n;i++)
            scanf("%d%d%d",&inp[i].first,&inp[i].second,&inp[i].third);
        
        sort(inp,inp+n,cmp);
        fill(tree,tree + n + 1 , INT_MAX);

        int ans = 0;
        for(int i=0; i<n; i++)
        {
            int curr = read(inp[i].second);
            if(curr > inp[i].third)
                ans++;
            update(inp[i].second,inp[i].third,n);
        }
        printf("%d\n",ans);
    }
    return 0;
}