/**************************************************************
    Problem: 1221
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:1692 ms
    Memory:1496 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<utility>
#include<queue>
#include<cstdlib>
 
typedef long long ll;
 
using namespace std;
 
namespace io {
    template<class T> void read(T&num) {
        static char CH; static bool F;
        F = false;
        for (CH = getchar(); CH<'0' || CH>'9'; F = CH == '-', CH = getchar());
        for (num = 0; CH >= '0'&&CH <= '9'; num = num * 10 + CH - '0', CH = getchar());
        F && (num = -num);
    }
 
    inline void space() { putchar(' '); }
 
    inline void ln() { putchar('\n'); }
 
    template<class T> inline void print(T p) {
        static int stk[70], tp;
        if (!p) { puts("0"); return; }
        while (p) stk[++tp] = p % 10, p /= 10;
        while (tp) putchar(stk[tp--] + '0');
    }
 
    template<class T> inline void println(T p) { print(p); ln(); }
}
 
using namespace io;
 
const int N = 2e3 + 5;
const int M = N * 16;
const int inf = 1e9;
 
struct Edge {
    int t, f, c;
    Edge() {}
    Edge(int t, int f, int c) :t(t), f(f), c(c) {}
} e[M];
 
int head[N], nx[M], ct = 1;
 
void insert(int s, int t, int f, int c) {
    nx[++ct] = head[s]; head[s] = ct; e[ct] = Edge(t, f, c);
    nx[++ct] = head[t]; head[t] = ct; e[ct] = Edge(s, 0, -c);
}
 
int d[N], a[N], inq[N], pre[M];
 
int mcf(int s, int t) {
    int cost = 0;
    while (1) {
        memset(d, 127, sizeof(d));
        memset(inq, 0, sizeof(inq));
        d[s] = 0; a[s] = inf;
        queue<int>q;
        q.push(s);
        inq[s] = 1;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            inq[x] = 0;
            for (int p = head[x]; p; p = nx[p]) {
                Edge& ee = e[p];
                if (d[ee.t] > d[x] + ee.c&&ee.f > 0) {
                    d[ee.t] = d[x] + ee.c;
                    a[ee.t] = min(ee.f, a[x]);
                    pre[ee.t] = p;
                    if (!inq[ee.t]) {
                        q.push(ee.t); inq[ee.t] = 1;
                    }
                }
            }
        }
        if (d[t] == 0x7f7f7f7f) break;
        cost += d[t] * a[t];
        int x = t;
        while (x != s) {
            e[pre[x]].f -= a[t];
            e[pre[x] ^ 1].f += a[t];
            x = e[pre[x] ^ 1].t;
        }
    }
    return cost;
}
 
int main() {
    int n, a, b, f, fA, fB, p;
    read(n); read(a); read(b); read(f); read(fA); read(fB);
    int S = 0, T = n * 2 + 1;
    for (int i = 1; i <= n; ++i) {
        read(p);
        insert(S, i, inf, f);
        insert(S, i + n, p, 0);
        insert(i, T, p, 0);
        if (i > 1) insert(n + i - 1, n + i, inf, 0);
        if (i + a + 1 <= n) insert(n + i, i + a + 1, inf, fA);
        if (i + b + 1 <= n) insert(n + i, i + b + 1, inf, fB);
    }
    println(mcf(S, T));
 
    return 0;
}