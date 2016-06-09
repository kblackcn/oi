/**************************************************************
    Problem: 3170
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:500 ms
    Memory:3936 kb
****************************************************************/
 
#include<cstdio>
#include<algorithm>
 
using namespace std;
 
const int N = 1e5 + 5;
 
typedef long long ll;
 
int x[N], y[N], n, t, p;
int xp[N], yp[N];
 
ll ans, blank, sx[N], sy[N];
 
int main() {
    scanf("%d", &n);
    if (n == 0) { puts("0"); return 0; }
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", xp + i, yp + i);
        x[i] = xp[i] + yp[i];
        y[i] = xp[i] - yp[i];
        xp[i] = x[i];
        yp[i] = y[i];
    }
    blank = 0;
    sort(x, x + n); sx[0] = x[0];
    sort(y, y + n); sy[0] = y[0];
    for (int i = 1; i < n; i++)
    {
        sx[i] = sx[i - 1] + x[i];
        sy[i] = sy[i - 1] + y[i];
    }
    ans = 1e18;
    for (int i = 0; i < n; i++)
    {
        int px = xp[i], py = yp[i];
        ll tmp = 0, pos;
 
        pos = lower_bound(x, x + n, px) - x;
        tmp += px*pos - sx[pos - 1] - px*(n - pos - 1) + (sx[n - 1] - sx[pos]);
 
        pos = lower_bound(y, y + n, py) - y;
        tmp += py*pos - sy[pos - 1] - py*(n - pos - 1) + (sy[n - 1] - sy[pos]);
 
        ans = min(ans, tmp);
    }
    printf("%lld\n", ans / 2);
}