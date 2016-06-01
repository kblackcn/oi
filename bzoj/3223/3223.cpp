/**************************************************************
    Problem: 3223
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:2708 ms
    Memory:2856 kb
****************************************************************/
 
#include<cstdio>
#include<algorithm>
 
using namespace std;
 
const int N = 1e5+5;
 
int fa[N], c[N][2], id[N];
int size[N];
bool rev[N];
 
int n, m, rt;
 
void pushdown(int k) {
    if(rev[k]) {
        int &l = c[k][0], &r = c[k][1];
        swap(l, r);
        rev[l]^=1; rev[r]^=1;
        rev[k] = 0;
    }
}
 
void pushup(int k) {
    size[k] = size[c[k][0]] + size[c[k][1]] + 1;
}
 
void build(int l, int r, int f) {
    if(l>r) return;
    int now = id[l], fx = id[f];
    if(l==r) {
        fa[now] = fx; size[now] = 1;
        if(l<f) c[fx][0] = now;
        else c[fx][1] = now;
        return;
    }
    int mid = (l+r) >> 1; now = id[mid];
    build(l, mid-1, mid); build(mid+1, r, mid);
    fa[now] = fx; pushup(mid);
    if(mid<f) c[fx][0] = now;
    else c[fx][1] = now;
}
 
void rotate(int x, int &k) {
    int y = fa[x], z = fa[y], l, r;
    if(c[y][0]==x) l = 0; else l = 1; r = l^1;
    if(y==k) k = x;
    else { if(c[z][0]==y) c[z][0] = x; else c[z][1] = x; }
    fa[x] = z; fa[y] = x; fa[c[x][r]] = y;
    c[y][l] = c[x][r]; c[x][r] = y;
    pushup(y); pushup(x);
}
 
void splay(int x, int&k) {
    while(x!=k) {
        int y = fa[x], z = fa[y];
        if(y!=k) {
            if(c[y][0]==x^c[z][0]==y)rotate(x, k);
            else rotate(y, k);
        }
        rotate(x, k);
    }
}
 
int find(int k, int rank) {
    pushdown(k);
    int l = c[k][0], r = c[k][1];
    if(size[l]+1==rank) return k;
    else if(size[l]>=rank) return find(l, rank);
    else return find(r, rank-size[l]-1);
}
 
void reverse(int l, int r) {
    int x = find(rt, l), y = find(rt, r+2);
    splay(x, rt); splay(y, c[x][1]);
    int z = c[y][0];
    rev[z]^=1;
}
 
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i<=n+2; ++i) id[i] = i;
    build(1, n+2, 0); rt = (n+3) >> 1;
    while(m-->0) {
        int l, r;
        scanf("%d%d", &l, &r);
        reverse(l, r);
    }
    for(int i = 2; i<=n+1; ++i)
        printf("%d ", find(rt, i)-1);
    return 0;
}