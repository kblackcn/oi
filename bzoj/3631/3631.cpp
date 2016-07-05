/**************************************************************
    Problem: 3631
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:1140 ms
    Memory:29724 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
 
typedef long long ll;
 
#define mp make_pair
 
namespace io {
 
    template<class T> void read(T&num) {
        static char CH; static bool F;
        F = false;
        for (CH = getchar(); CH<'0' || CH>'9'; F = CH == '-', CH = getchar());
        for (num = 0; CH >= '0'&&CH <= '9'; num = num * 10 + CH - '0', CH = getchar());
        F && (num = -num);
    }
 
    template<class T> inline void print(T p) {
        static int stk[70], tp;
        if (!p) { putchar('0'); return; }
        while (p) stk[++tp] = p % 10, p /= 10;
        while (tp) putchar(stk[tp--] + '0');
    }
 
    template<class T> inline void println(T p) {
        print(p);
        putchar('\n');
    }
 
    inline void space() {
        putchar(' ');
    }
 
    inline void ln() {
        putchar('\n');
    }
}
 
namespace basic {
    template<class T> T max(T& x, T& y) { return x > y ? x : y; }
    template<class T> T min(T& x, T& y) { return x < y ? x : y; }
 
    template<class T> T& upmax(T& x, T& y) { return y > x ? (x = y) : x; }
    template<class T> T& upmin(T& x, T& y) { return y < x ? (x = y) : x; }
}
 
const int N = 3e5 + 5;
const int M = N * 4;
 
using namespace io;
using namespace std;
 
struct RangeAdd {
    int a[N];
    void add(const int l, const int r, const int v) {
        a[l] += v;
        a[r + 1] -= v;
    }
    ll sum(const int n) {
        ll ans = 0; int now = 0;
        for (int i = 0; i < n; ++i) {
            ans += (now += a[i]);
        }
    }
} ra;
 
int route[N];
int ans[N];
 
vector<int> edges[N];
 
typedef vector<int>::iterator iter;
 
int belong[N], depth[N], fa[N], heavy[N], pos[N], rev[N], cur = 0;
 
int dfs(int p) {
    int size = 1, bs = 0, hs = -1;
    for (iter it = edges[p].begin(); it != edges[p].end(); ++it) {
        if (fa[p] == *it) continue;
        fa[*it] = p;
        depth[*it] = depth[p] + 1;
        int sz = dfs(*it);
        if (sz > bs) {
            bs = sz;
            hs = *it;
        }
    }
    heavy[p] = hs;
    return size;
}
 
void dfs2(int p) {
    pos[p] = ++cur; rev[cur] = p;
    if (heavy[p] == -1)return;
    belong[heavy[p]] = belong[p];
    dfs2(heavy[p]);
    for (iter it = edges[p].begin(); it != edges[p].end(); ++it) {
        if (fa[p] == *it || heavy[p] == *it) continue;
        belong[*it] = *it;
        dfs2(*it);
    }
}
 
void work(int x, int y) {
    int fx = belong[x], fy = belong[y];
    while (fx != fy) {
        if (depth[fx] < depth[fy]) {
            swap(x, y); swap(fx, fy);
        }
        ra.add(pos[fx], pos[x], 1);
        x = fa[fx];
        fx = belong[x];
    }
    if (depth[x] > depth[y]) {
        swap(x, y);
    }
    ra.add(pos[x], pos[y], 1);
}
 
int main() {
    int n;
    read(n);
    for (int i = 0; i < n; ++i) read(route[i]);
    for (int i = 1; i < n; ++i) {
        int x, y;
        read(x); read(y);
        edges[x].push_back(y);
        edges[y].push_back(x);
    }
    dfs(1);
    belong[1] = 1;
    dfs2(1);
    for (int i = 1; i < n; ++i) work(route[i - 1], route[i]);
    int now = -1;
     
    for (int i = 1; i <= n; ++i) {
        ans[rev[i]] = (now += ra.a[i]);
    }
    ++ans[route[0]];
    for (int i = 1; i <= n; ++i)println(ans[i]);
    return 0;
}