/**************************************************************
    Problem: 1196
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:184 ms
    Memory:1336 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
#include<algorithm>
 
typedef long long ll;
 
const int N = 2e4 + 5;
 
using namespace std;
 
template<class T> void read(T&num) {
    static char CH; static bool F;
    F = false;
    for (CH = getchar(); CH<'0' || CH>'9'; F = CH == '-', CH = getchar());
    for (num = 0; CH >= '0'&&CH <= '9'; num = num * 10 + CH - '0', CH = getchar());
    F && (num = -num);
}
 
inline void space() {
    putchar(' ');
}
 
inline void ln() {
    putchar('\n');
}
 
template<class T> inline void print(T p) {
    static int stk[70], tp;
    if (!p) { puts("0"); return; }
    while (p) stk[++tp] = p % 10, p /= 10;
    while (tp) putchar(stk[tp--] + '0');
}
 
template<class T> inline void println(T p) {
    print(p);
    ln();
}
 
struct UnionSet {
    int fa[10005];
 
    void reset(int n) {
        for (int i = 1; i <= n; ++i) {
            fa[i] = i;
        }
    }
 
    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
 
    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        fa[x] = y;
        return true;
    }
} us;
 
struct Edge {
    int s, t, c1, c2;
} e[N];
 
bool cmp1(int x, int y) { return e[x].c1 < e[y].c1; }
 
bool cmp2(int x, int y) { return e[x].c2 < e[y].c2; }
 
int p[N], q[N], n, k, m, mx, mi;
 
bool used[N];
 
bool check(const int mx) {
    memset(used, 0, sizeof(used));
    us.reset(n);
    int ks = k, ns = n - 1;
    for (int i = 0; i < m && e[q[i]].c2 <= mx && ks>0; ++i) if (!used[q[i]]) {
        if (us.merge(e[q[i]].s, e[q[i]].t)) {
            used[q[i]] = true;
            --ks; --ns;
        }
    }
    if (ks > 0) return false;
    for (int i = 0; i < m && e[p[i]].c1 <= mx && ns>0; ++i) if (!used[p[i]]) {
        if (us.merge(e[p[i]].s, e[p[i]].t)) {
            used[p[i]] = true;
            --ns;
        }
    }
    return ns == 0;
}
 
int main() {
    read(n); read(k); read(m); --m;
    mi = 1e9;
    for (int i = 0; i < m; ++i) {
        p[i] = q[i] = i;
        read(e[i].s); read(e[i].t);
        read(e[i].c2); read(e[i].c1);
        if (e[i].c2 > mx) mx = e[i].c2;
        if (e[i].c1 < mi) mi = e[i].c1;
    }
    sort(p, p + m, cmp1);
    sort(q, q + m, cmp2);
    int l = mi, r = mx;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid; else l = mid + 1;
    }
    println(l);
    return 0;
}