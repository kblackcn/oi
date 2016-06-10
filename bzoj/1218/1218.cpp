/**************************************************************
    Problem: 1218
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:3264 ms
    Memory:98852 kb
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
        if (!p) { puts("0"); return; }
        while (p) stk[++tp] = p % 10, p /= 10;
        while (tp) putchar(stk[tp--] + '0');
    }
 
    template<class T> inline void println(T p) { print(p); ln(); }
}
 
using namespace io;
 
#define M 5010
using namespace std;
int n, r, ans, sum[M][M];
int main()
{
    int i, j, x, y, z;
    read(n); read(r);
    for (i = 1; i <= n; i++)
        read(x), read(y), read(z), sum[x + 1][y + 1] += z;
    for (i = 1; i <= 5001; i++)
        for (j = 1; j <= 5001; j++)
            sum[i][j] += sum[i - 1][j];
    for (i = 1; i <= 5001; i++)
        for (j = 1; j <= 5001; j++)
            sum[i][j] += sum[i][j - 1];
    for (i = r; i <= 5001; i++)
        for (j = r; j <= 5001; j++)
            ans = max(ans, sum[i][j] + sum[i - r][j - r] - sum[i][j - r] - sum[i - r][j]);
    println(ans);
}