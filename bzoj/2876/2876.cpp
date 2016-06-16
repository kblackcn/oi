/**************************************************************
    Problem: 2876
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:1556 ms
    Memory:1116 kb
****************************************************************/
 
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
 
typedef long long ll;
 
namespace io {
 
    template<class T> T read() {
        T v;
        read(v);
        return v;
    }
 
    template<class T> void read(T&num) {
        static char ch; static bool F;
        F = false;
        for (ch = getchar(); ch<'0' || ch>'9'; F = ch == '-', ch = getchar());
        for (num = 0; ch >= '0'&&ch <= '9'; num = num * 10 + ch - '0', ch = getchar());
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
        if (!p) { putchar('0'); return; }
        while (p) stk[++tp] = p % 10, p /= 10;
        while (tp) putchar(stk[tp--] + '0');
    }
 
    template<class T> inline void println(T p) {
        print(p);
        ln();
    }
}
 
using namespace io;
using namespace std;
 
const int N = 1e4;
 
double s[N], k[N], v[N];
 
double t[N];
 
int n;
double E;
 
double sqr(double x) { return x*x; }
 
double caculate(double lambda) {
    double ans = 0;
    for (int i = 0; i < n; ++i) {
        double x = 10;
        int n = 25;
        while (n--)
            x -= (2 * k[i] * lambda*(x - v[i])*x*x - 1) / (6 * lambda*k[i] * x*x - 4 * lambda*k[i] * v[i] * x);
        t[i] = x;
        ans += s[i] * k[i] * sqr(x - v[i]);
    }
    return ans;
}
 
int main() {
    scanf("%d%lf", &n, &E);
    for (int i = 0; i < n; ++i) scanf("%lf%lf%lf", s + i, k + i, v + i);
    double l = 0, r = 1;
    int k = 80;
    while (k--) {
        double mid = (l + r) / 2;
        double use = caculate(mid);
        if (use > E) l = mid; else r = mid;
    }
    double ans = 0;
    for (int i = 0; i < n; ++i)ans += s[i] / t[i];
    printf("%.6f", ans);
    return 0;
}