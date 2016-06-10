/**************************************************************
    Problem: 1208
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:164 ms
    Memory:940 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<utility>
#include<set>
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
 
///
const int MOD = 1000000;
 
const int INF = 1e9;
 
typedef set<int>::iterator iter;
 
set<int> s;
 
int main() {
    int n, op, x, cur, ans = 0;
    s.insert(-INF);
    s.insert(INF);
    read(n);
    while (n--) {
        read(op); read(x);
        if (s.size() == 2) {
            cur = op;
            s.insert(x);
        }
        else if (op != cur) {
            iter lt = --s.lower_bound(x);
            iter rt = s.lower_bound(x);
            int l = x - *lt, r = *rt - x;
            if (l <= r) {
                ans += l;
                s.erase(lt);
            }
            else {
                ans += r;
                s.erase(rt);
            }
            ans %= MOD;
        }
        else s.insert(x);
    }
    println(ans);
    return 0;
}