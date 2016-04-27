/**************************************************************
    Problem: 1207
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:60 ms
    Memory:1000 kb
****************************************************************/
 
#include<cstdio>
 
const int N = 1e4 + 5;
 
int f[N], x[N], y[N], t[N], mx[N];
 
int abs(int x) { return x > 0 ? x : -x; }
 
int main() {
    int n, m, ans = 0;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d%d", t + i, x + i, y + i);
        for (int j = i - 1; j > -1; --j) {
            if (mx[j] + 1 <= f[i])break;
            if (abs(x[i] - x[j]) + abs(y[i] - y[j]) <= t[i] - t[j]) {
                if (f[j] + 1 > f[i]) f[i] = f[j] + 1;
            }
        }
        if (f[i] == 0)f[i] = 1;
        if (i > 0)mx[i] = mx[i - 1] > f[i] ? mx[i - 1] : f[i];
        else mx[i] = f[i];
        if (f[i] > ans)ans = f[i];
    }
    printf("%d\n", ans);
    return 0;
}