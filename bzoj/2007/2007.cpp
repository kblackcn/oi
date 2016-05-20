/**************************************************************
    Problem: 2007
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:716 ms
    Memory:61744 kb
****************************************************************/
 
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
const int N = 300000;
const int M = 3000000;
using namespace std;
 
int n,S,T,dis[N],head[N],next[M],to[M],len[M],cnt,size;
struct HEAP
{
    int x,d;
}heap[M];
inline void add(int u,int v,int w)
{
    to[cnt]=v; len[cnt]=w; next[cnt]=head[u]; head[u]=cnt++;
}
int getnum(int x,int y)
{
    return (x-1)*n+y;
}
inline bool cmp(const HEAP &a,const HEAP &b)
{
    return a.d>b.d;
}
void read()
{
    memset(head,-1,sizeof head);
    cnt=0;
    scanf("%d",&n);
    S=0; T=n*n+1;
    int a;
    for(int i=1;i<=n;i++) scanf("%d",&a),add(S,getnum(1,i),a);
    for(int i=1;i<n;i++)
        for(int j=1;j<=n;j++) 
            scanf("%d",&a),add(getnum(i,j),getnum(i+1,j),a);
    for(int i=1;i<=n;i++)
        scanf("%d",&a),add(getnum(n,i),T,a);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a),add(getnum(i,1),T,a);
        for(int j=2;j<=n;j++) scanf("%d",&a),add(getnum(i,j),getnum(i,j-1),a);
        scanf("%d",&a),add(S,getnum(i,n),a);
    }
    for(int i=1;i<=n;i++) scanf("%d",&a);
    for(int i=1;i<n;i++)
        for(int j=1;j<=n;j++) 
            scanf("%d",&a),add(getnum(i+1,j),getnum(i,j),a);
    for(int i=1;i<=n;i++) scanf("%d",&a);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a);
        for(int j=2;j<=n;j++) scanf("%d",&a),add(getnum(i,j-1),getnum(i,j),a);
        scanf("%d",&a);
    }
}
void dijkstra()
{
    memset(dis,127,sizeof dis);
    heap[1].x=S; heap[1].d=0; dis[S]=0; size=1;
    int sta;
    while(size)
    {
        sta=heap[1].x;
        pop_heap(heap+1,heap+1+size,cmp);
        size--;
        for(int i=head[sta];~i;i=next[i])
            if(dis[to[i]]>dis[sta]+len[i])
            {
                dis[to[i]]=dis[sta]+len[i];
                size++;
                heap[size].x=to[i]; heap[size].d=dis[to[i]];
                push_heap(heap+1,heap+1+size,cmp);
            }
    }
     
    printf("%d\n",dis[T]);
}
int main()
{
    read();
    dijkstra();
    return 0;
}