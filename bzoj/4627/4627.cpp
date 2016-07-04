/**************************************************************
    Problem: 4627
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:504 ms
    Memory:3168 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
 
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
 
using namespace io;
using namespace std;
 
struct BIT {
    int a[N];
    void add(int x, int v) { for (; x < N; x = (x << 1) - (x&(x - 1))) a[x] += v; }
    int sum(int x) { int ans; for (ans = 0; x > 0; x = x&(x - 1))ans += a[x]; return ans; }
} bit;
 
int a[N];
ll sum[N];
ll li[N];
 
int main() {
    int n, m = 0, L, R;
    read(n); read(L); read(R); if (L > R) { puts("0"); return 0; }
    for (int i = 1; i <= n; ++i)read(a[i]), li[i] = sum[i] = sum[i - 1] + a[i];
    sort(li + 1, li + 1 + n);
    li[0] = -1e19;
    for (int i = 1; i <= n; ++i) { if (li[i] != li[i - 1]) li[++m] = li[i]; bit.add(m, 1); }
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        ll *x = lower_bound(li + 1, li + 1 + m, sum[i] + L);
        ll *y = upper_bound(li + 1, li + 1 + m, sum[i] + R);
        if (*x >= sum[i] + L)--x;
        if (*y > sum[i] + R)--y;
        ans += bit.sum(y - li) - bit.sum(x - li);
        bit.add(lower_bound(li + 1, li + 1 + m, sum[i + 1]) - li, -1);
    }
    println(ans);
    return 0;
}