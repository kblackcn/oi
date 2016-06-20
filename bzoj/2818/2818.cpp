/**************************************************************
    Problem: 2818
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:996 ms
    Memory:166820 kb
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
 
const int N = 1e7 + 5;
 
int n;
int p[N], phi[N], pc;
ll sum[N];
bool np[N];
 
void getphi() {
    phi[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!np[i]) { phi[i] = i - 1; p[pc++] = i; }
        for (int j = 0, k; j < pc; ++j) {
            if (i*(k = p[j]) > n)break;
            np[i*k] = true;
            if (i%k == 0) { phi[i*k] = phi[i] * k; break; }
            phi[i*k] = phi[i] * phi[k];
        }
    }
}
 
int main() {
    read(n);
    getphi();
    for (int i = 1; i <= n; ++i) sum[i] = sum[i - 1] + phi[i];
    ll ans = 0;
    for (int i = 0; i < pc; ++i) {
        ans += sum[n / p[i]] * 2 - 1;
    }
    println(ans);
    return 0;
}