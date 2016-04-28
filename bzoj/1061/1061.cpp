/**************************************************************
    Problem: 1061
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:1352 ms
    Memory:2876 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
 
const int N = 1e3+5;
const int M = 1e5+5;
const int inf = 1e8;
 
int need[N];
 
int head[N], next[M], S, T, ct;
 
struct Edge {
    int tar, w, c;
    Edge() {}
    Edge(int a, int b, int c):tar(a), w(b), c(c) {}
} e[M];
 
void insert(int x, int y, int w, int c) {
    next[ct] = head[x]; head[x] = ct; e[ct] = Edge(y, w, c); ++ct;
    next[ct] = head[y]; head[y] = ct; e[ct] = Edge(x, 0, -c); ++ct;
}
 
int q[M], le[N], lp[N], c[N];
bool iq[M];
 
bool spfa() {
    memset(c, 127, sizeof(c));
    int std = c[0];
    int l = 0, r = 1;
    iq[S] = true;
    c[S] = 0;
    q[0] = S;
    while(l<r) {
        int p = q[l++];
        for(int ei = head[p]; ei>-1; ei = next[ei]) if(e[ei].w>0) {
            int j = e[ei].tar;
            if(c[p] + e[ei].c < c[j]) {
                c[j] = c[p] + e[ei].c;
                le[j] = ei; lp[j] = p;
                if(!iq[j]) {
                    q[r++] = j;
                    iq[j] = true;
                }
            }
        }
        iq[p] = false;
    }
    return c[T] < std;
}
 
int dig() {
    int w = inf;
    for(int i = T; i!=S; i = lp[i]) if(e[le[i]].w<w) w = e[le[i]].w;
    for(int i = T; i!=S; i = lp[i]) {
        int x = le[i];
        e[x].w-=w; e[x^1].w+=w;
    }
    return c[T] * w;
}
 
int main() {
    memset(head, -1, sizeof(head));
    int n, m;
    scanf("%d%d", &n, &m);
    S = n+2, T = n+3;
    for(int i = 1; i<=n; ++i)
           scanf("%d", need+i);
    for(int i = 1; i<=n+1; ++i) {
           int d = need[i] - need[i-1];
           if(d>0) insert(S, i-1, d, 0);
           else insert(i-1, T, -d, 0);
    }
    for(int i = n; i>0; --i) {
        insert(i, i-1, inf, 0);
    }
    for(int i = 0; i<m; ++i) {
        int s, t, c;
        scanf("%d%d%d", &s, &t, &c);
        insert(s-1, t, inf, c);
    }
    int ans = 0;
    while(spfa())
        ans += dig();
    printf("%d\n", ans);
    return 0;
}