/**************************************************************
    Problem: 1013
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:0 ms
    Memory:1272 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
 
const double eps = 1e-6;
 
const int N = 10 + 2;
 
int n;
 
double f[N];
 
double a[N][N];
 
double sqr(double t) { return t*t; }
 
void swap(double& x, double& y) { double t = x; x = y; y = t; }
 
int gauss() {
    int now = 1, to; double t;
    for (int i = 1; i <= n; i++)
    {
        for (to = now; to <= n; to++)if (fabs(a[to][i]) > eps)break;
        if (to > n)continue;
        if (to != now)for (int j = 1; j <= n + 1; j++)
            swap(a[to][j], a[now][j]);
        t = a[now][i];
        for (int j = 1; j <= n + 1; j++)a[now][j] /= t;
        for (int j = 1; j <= n; j++)
            if (j != now)
            {
                t = a[j][i];
                for (int k = 1; k <= n + 1; k++)
                    a[j][k] -= t*a[now][k];
            }
        now++;
    }
    for (int i = now; i <= n; i++)
        if (fabs(a[i][n + 1]) > eps)return 0;
    return 1;
}
 
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)scanf("%lf", f + i);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j) {
            double t;
            scanf("%lf", &t);
            a[i][j] = 2 * (t - f[j]);
            a[i][n + 1] += sqr(t) - sqr(f[j]);
        }
    gauss();
    for (int i = 1; i <= n - 1; i++)
        printf("%.3lf ", a[i][n + 1]);
    printf("%.3lf\n", a[n][n + 1]);
    return 0;
}