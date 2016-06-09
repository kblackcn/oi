/**************************************************************
    Problem: 3173
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:712 ms
    Memory:3544 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<utility>
#include<cstdlib>
 
typedef long long ll;
 
const int N = 1e5 + 5;
 
using namespace std;
 
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
 
int sz[N], rnd[N], l[N], r[N], cnt;
 
void update(int x)
{
    sz[x] = sz[l[x]] + sz[r[x]] + 1;
}
void rturn(int &k)
{
    int t = l[k]; l[k] = r[t]; r[t] = k; update(k); update(t); k = t;
}
void lturn(int &k)
{
    int t = r[k]; r[k] = l[t]; l[t] = k; update(k); update(t); k = t;
}
void insert(int &x, int rank)
{
    if (!x)
    {
        x = ++cnt;
        rnd[x] = rand(); sz[x] = 1;
        return;
    }
    sz[x]++;
    if (sz[l[x]] < rank)
    {
        insert(r[x], rank - sz[l[x]] - 1);
        if (rnd[r[x]] < rnd[x])lturn(x);
    }
    else
    {
        insert(l[x], rank);
        if (rnd[l[x]] < rnd[x])rturn(x);
    }
}
 
int v[N], now, mn[N], mx, ans[N];
 
void dump(int x) {
    if (!x)return;
    dump(l[x]);
    v[++now] = x;
    dump(r[x]);
}
 
int n, x, k, root;
 
void solve()
{
    memset(mn, 127, sizeof(mn));
    mn[0] = -1e9;
    for (int i = 1; i <= n; i++)
    {
        int t = upper_bound(mn, mn + mx + 1, v[i]) - mn;
        if (mn[t - 1] <= v[i])
        {
            mn[t] = min(mn[t], v[i]);
            ans[v[i]] = t;
            mx = max(t, mx);
        }
    }
}
 
int main() {
    read(n);
    srand(n ^ 564);
    for (int i = 0; i < n; ++i) {
        read(x);
        insert(root, x);
    }
    dump(root);
    solve();
    for (int i = 1; i <= n; i++)
    {
        ans[i] = max(ans[i - 1], ans[i]);
        println(ans[i]);
    }
    return 0;
}