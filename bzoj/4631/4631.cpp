/**************************************************************
    Problem: 4631
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:916 ms
    Memory:4728 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
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
 
const int N = 1e5 + 5;
const int M = N * 4;
 
using namespace io;
using namespace std;
 
typedef pair<int, int> par;
 
int v[M];
 
par ax[N];
int pos[N];
 
int merge(int x, int y) {
    return ax[x].first > ax[y].first ? x : y;
}
 
void build(int id, int l, int r) {
    if (l == r) { v[id] = l; pos[l] = id; return; }
    int mid = (l + r) >> 1;
    build(id << 1, l, mid); build((id << 1) + 1, mid + 1, r);
    v[id] = merge(v[id << 1], v[(id << 1) + 1]);
}
 
int query(int id, int l, int r, int MR) {
    if (l == r) return ax[l].second <= MR ? v[id] : 0;
    int mid = (l + r) >> 1;
    if (ax[r].second <= MR) return v[id];
    if (ax[mid + 1].second <= MR) return merge(v[id << 1], query((id << 1) + 1, mid + 1, r, MR));
    query((id << 1), l, mid, MR);
}
 
void change(int x) {
    int id = pos[x];
    v[id] = 0; id >>= 1;
    while (id > 0) {
        v[id] = merge(v[id << 1], v[(id << 1) + 1]);
        id >>= 1;
    }
}
 
bool cmp(const par& x, const par& y) { return x.first < y.first; }
bool cmp2(const par& x, const par& y) { return x.second < y.second || (x.second == y.second && x.first < y.first); }
 
int still[N], ans;
 
int suff[N], pre[N];
 
int main() {
    int n, m, q;
    read(n); read(m);
    for (int i = 1; i <= n; ++i) read(still[i]), suff[i] = i + 1, pre[i] = i - 1;
    for (int i = 1; i <= m; ++i) read(ax[i].first), read(ax[i].second);
    sort(ax + 1, ax + m + 1, cmp2);
    build(1, 1, m);
    read(q);
    while (q--) {
        int x; read(x);
        x = (x + ans - 1) % n + 1;
        --still[x];
        if (still[x] == 0) {
            int l = pre[x], r = suff[x];
            suff[l] = r; pre[r] = l;
            while (1) {
                int t = query(1, 1, m, r - 1);
                if (ax[t].first <= l) break;
                ++ans;
                change(t);
            }
        }
        println(ans);
    }
    return 0;
}