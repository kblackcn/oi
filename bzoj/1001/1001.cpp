/**************************************************************
    Problem: 1001
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:400 ms
    Memory:89168 kb
****************************************************************/
 
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
 
using namespace std;
 
const int N=2000006, INF=0x3fffffff, E=N*3;
 
struct ARC {
    int u, val, next;
    inline void init(int a, int b, int c) {
        u=a, val=b, next=c;
    }
} arc[E];
int head[N], tot, S, T, n, m, dis[N];
bool vs[N];
 
struct data {
    int u, dis;
    data() {}
    data(int a, int b) : u(a), dis(b) {}
    bool operator < (const data &T) const {
        return dis>T.dis;
    }
};
 
inline void add_arc(int s, int t, int val) {
    arc[tot].init(t, val, head[s]);
    head[s]=tot++;
}
 
priority_queue <data> Q;
void Dijkstra() {
    fill(dis, dis+T+1, INF);
    fill(vs, vs+T+1, 0);
    while(!Q.empty()) Q.pop();
    dis[S]=0, Q.push(data(S, 0));
    for(int u; !Q.empty(); ) {
        u=Q.top().u, Q.pop();
        if(vs[u]) continue;
        if(u==T) {
            printf("%d\n", dis[T]);
            break;
        }
        vs[u]=1;
        for(int e=head[u]; e!=-1; e=arc[e].next) {
            int v=arc[e].u;
            if(vs[v] || dis[u]+arc[e].val>=dis[v]) continue;
            dis[v]=dis[u]+arc[e].val;
            Q.push(data(v, dis[v]));
        }
    }
}
 
void read(int &x) {
    char c;
    while((c=getchar())<'0' || c>'9');
    x=c-'0';
    while((c=getchar())>='0' && c<='9') x=(x<<3)+(x<<1)+c-'0';
}
 
void Input() {
    for(int i=0, id1, id2, a; i<=n-1; i++)
        for(int j=1; j<=m-1; j++) {
            read(a);
            id1=((i-1)*(m-1)+j)*2-1;
            id2=(i*(m-1)+j)*2;
            if(i==0) id1=T;
            else if(i==n-1) id2=S;
            add_arc(id1, id2, a);
            add_arc(id2, id1, a);
        }
 
    for(int i=1, id1, id2, a; i<=n-1; i++)
        for(int j=0; j<m; j++) {
            read(a);
            id1=((i-1)*(m-1)+j)*2;
            id2=((i-1)*(m-1)+j+1)*2-1;
            if(j==0) id1=S;
            else if(j==m-1) id2=T;
            add_arc(id1, id2, a);
            add_arc(id2, id1, a);
        }
 
    for(int i=1, id1, id2, a; i<=n-1; i++)
        for(int j=1; j<=m-1; j++) {
            read(a);
            id1=((i-1)*(m-1)+j)*2;
            id2=((i-1)*(m-1)+j)*2-1;
            add_arc(id1, id2, a);
            add_arc(id2, id1, a);
        }
}
 
int main() {
    read(n), read(m);
    S=0, T=(n-1)*(m-1)*2+1;
    fill(head, head+T+1, -1), tot=0;
    if(n==1 || m==1) {
        if(n>m) swap(n, m);
        int ans=INF;
        for(int i=1, a; i<m; i++) {
            read(a);
            if(ans>a) ans=a;
        }
        printf("%d\n", ans==INF?0:ans);
    }
    else Input(), Dijkstra();
    return 0;
}