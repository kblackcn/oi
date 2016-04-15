/**************************************************************
    Problem: 4532
    User: qwerty123456
    Language: C++
    Result: Accepted
    Time:944 ms
    Memory:114088 kb
****************************************************************/
 
#include<cctype>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
 
using namespace std;
const int N = 5e5 + 5;
 
int n, l, r, s, num[N], pn, np[N], pr[N], y[N], e[N], z[N], ans = 0, c[N][52];
 
void getprime()
{
    pn = 0, z[0] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!np[i]) e[i] = 1, y[i] = 2, pr[pn++] = i;
        for (int j = 0; j < pn && pr[j] * i <= n; j++)
        {
            np[pr[j] * i] = 1;
            if (i%pr[j] == 0) {
                y[i*pr[j]] = y[i] / (e[i] + 1)*(e[i] + 2), e[i*pr[j]] = e[i] + 1;
                break;
            }
            e[i*pr[j]] = 1, y[i*pr[j]] = y[i] * y[pr[j]];
        }
        z[i - 1] = z[i - 2] + y[i];
    }
 
}
void solve(int t) {
    int mistake = 0;
    for (int r = n - 1, l = r + 1; r >= 0; --r) {
        while (l > 0) {
            int x = num[l - 1], y = ((l - 1) % t);
            if (c[y][x] == 0) {
                ++c[y][x];
                --l;
            }
            else break;
        }
        int k = (r - l + 1) / t;
        if (k >= s) {
            int v = z[r] - z[r - t*k];
            if (v > ans) ans = v;
        }
        --c[r%t][num[r]];
    }
}
int main() {
    scanf("%d%d%d%d", &n, &l, &r, &s);
    getprime();
    for (int i = 0; i < n; ++i) {
        char ch;
        do { ch = getchar(); } while (!isalpha(ch));
        num[i] = ch <= 'Z' ? (ch - 'A' + 26) : (ch - 'a');
    }
    for (int i = l; i <= r; ++i) solve(i);
    printf("%d\n", ans);
    return 0;
}