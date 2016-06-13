/**************************************************************
    Problem: 1009
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:24 ms
    Memory:812 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<utility>
#include<queue>
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
        if (!p) { putchar('0'); return; }
        while (p) stk[++tp] = p % 10, p /= 10;
        while (tp) putchar(stk[tp--] + '0');
    }
 
    template<class T> inline void println(T p) { print(p); ln(); }
}
 
using namespace io;
 
const int N = 20 + 5;
 
struct matrix {
    int dat[N][N];
    void clear() {
        memset(dat, 0, sizeof(dat));
    }
};
 
int MSIZE, P, n, m;
 
char st[N];
int nx[N];
 
void multi(const matrix x, const matrix y, matrix& z) {
    memset(z.dat, 0, sizeof(z.dat));
    for (int i = 0; i < MSIZE; ++i)
        for (int j = 0; j < MSIZE; ++j)
            for (int k = 0; k < MSIZE; ++k) {
                z.dat[i][j] += x.dat[i][k] * y.dat[k][j];
            }
    for (int i = 0; i < MSIZE; ++i)
        for (int j = 0; j < MSIZE; ++j) {
            z.dat[i][j] %= P;
        }
}
 
matrix a, b;
 
int main() {
    read(n); read(m); read(P); MSIZE = m;
    scanf("%s", st + 1);
    int j = 0;
    for (int i = 2; i <= m; i++)
    {
        while (j > 0 && st[j + 1] != st[i])j = nx[j];
        if (st[j + 1] == st[i])j++;
        nx[i] = j;
    }
    for (int i = 0; i < m; i++)
        for (int j = 0; j <= 9; j++)
        {
            int t = i;
            while (t > 0 && st[t + 1] - '0' != j)
                t = nx[t];
            if (st[t + 1] - '0' == j)t++;
            if (t != m)b.dat[t][i] = (b.dat[t][i] + 1) % P;
        }
    for (int i = 0; i < m; i++)
        a.dat[i][i] = 1;
    while (n > 0) {
        if (n & 1)multi(a, b, a);
        multi(b, b, b);
        n >>= 1;
    }
    int ans = 0;
    for (int i = 0; i < m; i++)
        ans = (ans + a.dat[i][0]) % P;
    println(ans);
    return 0;
}