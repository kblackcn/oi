/**************************************************************
    Problem: 1211
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:0 ms
    Memory:812 kb
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
 
const int N = 155;
 
int p[N], np[N], pc;
 
int ans[N];
 
inline void getPrime() {
    for (int i = 2; i < N; ++i) {
        if (!np[i]) {
            p[pc++] = i;
        }
        for (int j = 0; j < pc && i*p[j] < N; ++j) {
            np[i*p[j]] = true;
            if (i%p[j] == 0)break;
        }
    }
}
 
inline void primeMultiply(int x, int op) {
    for (int i = 0; i < pc; ++i) {
        while (x%p[i] == 0) {
            x /= p[i];
            ans[i] += op;
        }
        if (x == 1)break;
    }
}
 
const int INF = 1e9;
 
int d[N];
int n, x;
 
int main() {
    getPrime();
    read(n);
    if (n == 1) {
        read(x);
        println(x == 0 ? 1 : 0);
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        read(d[i]);
        x += d[i];
        if (d[i] == 0) {
            println(0);
            return 0;
        }
    }
    if (x + 2 != n * 2) {
        println(0);
        return 0;
    }
    for (int i = 2; i < n - 1; ++i) primeMultiply(i, 1);
    for (int i = 0; i < n; i++)
        for (int j = 2; j < d[i]; j++)
            primeMultiply(j, -1);
    long long ret = 1;
    for (int i = 0; i < pc; ++i)
        while (ans[i]--) {
            ret *= p[i];
        }
    println(ret);
    return 0;
}