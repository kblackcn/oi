/**************************************************************
    Problem: 3143
    User: shzhw
    Language: C++
    Result: Accepted
    Time:668 ms
    Memory:7788 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
 
const int N = 500 + 5;
const int M = N*N;
const double eps = 1e-9;
 
int du[N], n, m;
 
struct Edge {
    int from, to;
    Edge() {}
    Edge(int x, int y) :from(x), to(y) {}
} e[M];
 
int head[N], next[M], tot(0);
 
void insert(int x, int y) {
    e[tot] = Edge(x, y); next[tot] = head[x]; head[x] = tot++;
    e[tot] = Edge(y, x); next[tot] = head[y]; head[y] = tot++;
    ++du[x]; ++du[y];
}
 
double a[N][N];
 
bool isZero(long double& x) {
    return fabs(x) < eps;
}
 
bool isZero(double& x) {
    return fabs(x) < eps;
}
 
void swap(double &x, double &y) {
    double t = x; x = y; y = t;
}
 
void gauss() {
    int std;
    for (int i = 1; i <= n; ++i) {
        std = i;
        for (int j = i + 1; j <= n; j++) if (fabs(a[j][i]) > fabs(a[std][i])) std = j;
        if (std > i) {
            for (int j = 1; j <= n + 1; ++j)
                swap(a[i][j], a[std][j]);
            std = i;
        }
        if (isZero(a[std][i]))continue;
        for (int k = i + 1; k <= n; ++k) {
            long double x = a[k][i] / a[std][i];
            for (int j = i; j <= n + 1; ++j) a[k][j] -= x*a[i][j];
        }
    }
    for (int i = n; i > 0; --i) {
        a[i][n + 1] /= a[i][i];
        for (int j = i - 1; j > 0; --j) {
            a[j][n + 1] -= a[i][n + 1] * a[j][i];
        }
    }
 
}
 
double v[M];
 
int main() {
    memset(head, -1, sizeof(head));
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        insert(u, v);
    }
    --n;
    for (int i = 1; i <= n; ++i) {
        a[i][i] = 1.0;
        for (int j = head[i]; j > -1; j = next[j]) if (e[j].to <= n)
            a[i][e[j].to] = -1.0 / du[e[j].to];
    }
    a[1][n + 1] = 1.0;
    gauss();
    for (int i = 0; i < tot; i += 2) {
        v[i >> 1] = a[e[i].from][n + 1] / du[e[i].from] + a[e[i].to][n + 1] / du[e[i].to];
    }
    tot >>= 1;
    std::sort(v, v + tot);
    double ans = 0;
    for (int i = tot; i > 0; --i) {
        ans += v[tot - i] * i;
    }
    printf("%.3lf\n", ans);
    return 0;
}