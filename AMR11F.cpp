#include <fstream>
#include <functional>
#include <climits>
#include <vector>
#include <queue>
#include <iostream>
#include <assert.h>
#include <map>
#include <stdlib.h>
#include <algorithm> 

#define mp make_pair

using namespace std;

#define LL long long
#define MAX 11000000
inline void scan(int *a) {
    register char c=0;
    while (c < 33)
        c = getchar();
    *a = 0;
    while (c > 33) {
        *a = *a * 10 + c - '0';
        c = getchar();
    }
}
static void print(int n) {
#define BSIZE 16
    char buf[BSIZE];
    int bn = BSIZE-1;
    while (1) {
        buf[bn--] = '0'+(n%10);
        n = n / 10;
        if (n == 0) break;
    }
    while (bn<BSIZE-1) putchar(buf[++bn]);
    putchar('\n');
}

struct node {
  int tower;
  int floorNum;
  int weight;
  node(int t, int f, int w) : tower(t), floorNum(f), weight(w) { };
  node() { }
};

class CompareGreater {
  public:
    bool const operator()(node &nodeX, node &nodeY) {
      return (nodeX.weight > nodeY.weight) ;
    }
};

bool compareByFloor(const node &a, const node &b) {
    return a.floorNum < b.floorNum;
}

int main() {

  int T;
    scan(&T);
    while (T--) {
        int N, F, M;
        scan(&N);
        scan(&F);
        scan(&M);
        int V = N + 2*M;
        vector<int> ref[N];
        map<pair<int, int> , int> ma;
        int graph[V][V];
        for (int i = 0; i < V; ++i) {
          for (int j = 0; j < V; ++j) {
            graph[i][j] = MAX;
          }
          graph[i][i] = 0;
        }
        int count = N-1;
        for (int i = 0; i < N-1; ++i) {
                    //addEdge(i, 0, i + 1, 0, 1);
                    ma[mp(i, 0)] = i;
                    graph[i][i+1] = graph[i+1][i] = 1;
                    ref[i].push_back(0);
        }
        //addEdge(N-1, 0, 0, 0, 1);
        graph[N-1][0] = graph[0][N-1] = 1;
        ma[mp(N-1, 0)] = N-1;
        ref[N-1].push_back(0);
        for (int i = 0; i < M; ++i) {
            int fx, tx, fy, ty, w;
            scan(&tx); scan(&fx); scan(&ty); scan(&fy); scan(&w);
            int r,s;
            if (!ma[mp(tx-1, fx-1)]) {
              if (!(ty-1 == 0 && fy-1 == 0)) {
                ma[mp(tx-1, fx-1)] = ++count;
                r = count;
                ref[tx-1].push_back(fx-1);
              } else {
                r=0;
              }
            } else
                r = ma[mp(tx-1, fx-1)];

            if (!ma[mp(ty-1, fy-1)]) {
              if (!(ty-1 == 0 && fy-1 == 0)) {
                ma[mp(ty-1, fy-1)] = ++count;
                s = count;
                ref[ty-1].push_back(fy-1);
              } else {
                s = 0;
              }
              
            } else {
              s = ma[mp(ty-1, fy-1)];
            }
            
            //cout<<"r = "<<r<<" s = "<<s<<" graph = "<<graph[r][s]<<endl;
            graph[s][r] = graph[r][s] = min(graph[r][s], w);
            //cout<<"r = "<<r<<" s = "<<s<<" graph = "<<graph[r][s]<<endl;
        }
        for (int i = 0; i < N; ++i) {
          sort(ref[i].begin(), ref[i].end());
        }
        for (int i = 0; i < N; ++i) {
          for (int j = 0; j < ref[i].size()-1; ++j) {
            graph[ma[mp(i, ref[i][j])]][ma[mp(i, ref[i][j+1])]] =
              graph[ma[mp(i, ref[i][j+1])]][ma[mp(i, ref[i][j])]] =
               min(ref[i][j+1] - ref[i][j], graph[ma[mp(i, ref[i][j+1])]][ma[mp(i, ref[i][j])]]);
            //cout<<"( "<<i<<" , "<<ref[i][j]<<" ) --- ( "<<i<<" , "<<ref[i][j+1]<<" )"<<endl;
          }
        }
/*
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
               if (graph[i][j] == MAX)
                   printf("%7s", "INF");
               else
                   printf ("%7d", graph[i][j]);
            }
            printf("\n");
        }
*/
        int i, j, k;
        for (k = 0; k < V; k++) {
        // Pick all vertices as source one by one
            for (i = 0; i < V; i++) {
                for (j = 0; j < V; j++) {
                    graph[i][j]=min(graph[i][j],graph[i][k]+graph[k][j]);
                    //cout<<" i = "<<i<<" j = "<<j<<" graph = "<<graph[i][j]<<endl;
                }
            }
        }

        

        int q;
        scan(&q);
        for (int i = 0; i < q; ++i) {
            int qtx, qfx, qty, qfy;
            scan(&qtx); scan(&qfx); scan(&qty); scan(&qfy);
            --qtx; --qfx; --qty; -- qfy;
            
            int nearestStartFloorUp = lower_bound(ref[qtx].begin(), ref[qtx].end(), qfx) - ref[qtx].begin();
            int nearestStartFloorDn = nearestStartFloorUp - 1;
            nearestStartFloorUp = ref[qtx][nearestStartFloorUp];
            if (nearestStartFloorDn >= 0)
              nearestStartFloorDn = ref[qtx][nearestStartFloorDn];
            else
              nearestStartFloorDn = 0;

            int nearestFinalFloorUp = lower_bound(ref[qty].begin(), ref[qty].end(), qfy) - ref[qty].begin();
            int nearestFinalFloorDn = nearestFinalFloorUp-1;
            nearestFinalFloorUp = ref[qty][nearestFinalFloorUp];
            if (nearestFinalFloorDn >= 0)
              nearestFinalFloorDn = ref[qty][nearestFinalFloorDn];
            else
              nearestFinalFloorDn = 0;

            int startDiffUp = abs(qfx-nearestStartFloorUp);
            int startDiffDn = abs(qfx-nearestStartFloorDn);
            //cout<<"Nearest Floor Down = "<<nearestStartFloorDn<<" Nearest Floor Up = "<<nearestStartFloorUp<<endl;

            int finalDiffUp = abs(qfy-nearestFinalFloorUp); 
            int finalDiffDn = abs(qfy-nearestFinalFloorDn); 
            //cout<<"Nearest Floor Down = "<<nearestFinalFloorDn<<" Nearest Floor Up = "<<nearestFinalFloorUp<<endl;

            int ans1 = graph[ma[mp(qtx, nearestStartFloorUp)]][ma[mp(qty, nearestFinalFloorUp)]];
            int ans2 = graph[ma[mp(qtx, nearestStartFloorDn)]][ma[mp(qty, nearestFinalFloorDn)]];
            int ans3 = graph[ma[mp(qtx, nearestStartFloorDn)]][ma[mp(qty, nearestFinalFloorUp)]];
            int ans4 = graph[ma[mp(qtx, nearestStartFloorUp)]][ma[mp(qty, nearestFinalFloorDn)]];
            //cout<<"ans1 = "<<ans1<<endl<<"ans2 = "<<ans2<<endl<<"ans3 = "<<ans3<<endl<<"ans4 = "<<ans4<<endl;
            ans1 += startDiffUp + finalDiffUp;
            ans1 = min(ans1, ans2 + startDiffDn + finalDiffDn);
            ans1 = min(ans1, ans3 + startDiffDn + finalDiffUp);
            ans1 = min(ans1, ans4 + startDiffUp + finalDiffDn);
            if (qtx == qty) {
              ans1 = min(ans1, abs(qfy - qfx));
            }
            print(ans1);
        }
    }

  return 0;
}