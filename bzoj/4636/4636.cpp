/**************************************************************
    Problem: 4636
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:596 ms
    Memory:2564 kb
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
 
const int N = 4e4 + 5;
 
using namespace io;
using namespace std;
 
typedef pair<int, int> pr;
 
pr l[N];
pr r[N];
 
bool cmp(const pr& x, const pr& y) {
    return x.first < y.first;
}
 
priority_queue<int> pq;
map<int, int> m;
 
int main() {
    int n;
    read(n);
    for (int i = 0; i < n; ++i) {
        int L, R, k;
        read(L); read(R); read(k);
        l[i] = mp(L, k);
        r[i] = mp(R, k);
        m[k] = 0;
    }
    sort(l, l + n, cmp); l[n].first = 1e9 + 2;
    sort(r, r + n, cmp); r[n].first = 1e9 + 1;
    int last = 0, li = 0, ri = 0;
    long long ans = 0;
    while (ri < n) {
        int now = min(l[li].first, r[ri].first);
        ans += pq.size() > 0 ? pq.top()*(now - last) : 0;
        while (r[ri].first == now) {
            ++m[r[ri++].second];
        }
        while (pq.size() > 0 && m[pq.top()] > 0) {
            --m[pq.top()]; pq.pop();
        }
        while (l[li].first == now) {
            pq.push(l[li++].second);
        }
        last = now;
    }
    println(ans);
    return 0;
}