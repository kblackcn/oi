/**************************************************************
    Problem: 3506
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:4392 ms
    Memory:4812 kb
****************************************************************/
 
#include<cstdio>
#include<algorithm>
 
using namespace std;
 
typedef long long ll;
 
const int N = 1e5 + 5;
const ll inf = 1e18;
 
int fa[N], c[N][2], sz[N];
bool rev[N];
 
ll a[N], v[N], mi[N];
 
 
int n, rt;
 
void pushdown(int k) {
    if (rev[k]) {
        int &l = c[k][0], &r = c[k][1];
        swap(l, r);
        rev[l] ^= 1; rev[r] ^= 1;
        rev[k] = 0;
    }
}
 
void pushup(int k) {
    sz[k] = sz[c[k][0]] + sz[c[k][1]] + 1;
    mi[k] = min(v[k], min(mi[c[k][0]], mi[c[k][1]]));
}
 
void build(int l, int r, int f) {
    if (l > r) return;
    int now = l, fx = f;
    if (l == r) {
        fa[now] = fx; sz[now] = 1;
        mi[now] = v[now];
        if (l < f) c[fx][0] = now;
        else c[fx][1] = now;
        return;
    }
    int mid = (l + r) >> 1; now = mid;
    build(l, mid - 1, mid); build(mid + 1, r, mid);
    fa[now] = fx; pushup(mid);
    if (mid < f) c[fx][0] = now;
    else c[fx][1] = now;
}
 
void rotate(int x, int &k) {
    int y = fa[x], z = fa[y], l, r;
    if (c[y][0] == x) l = 0; else l = 1; r = l ^ 1;
    if (y == k) k = x;
    else { if (c[z][0] == y) c[z][0] = x; else c[z][1] = x; }
    fa[x] = z; fa[y] = x; fa[c[x][r]] = y;
    c[y][l] = c[x][r]; c[x][r] = y;
    pushup(y); pushup(x);
}
 
void splay(int x, int&k) {
    while (x != k) {
        int y = fa[x], z = fa[y];
        if (y != k) {
            if (c[y][0] == x^c[z][0] == y)rotate(x, k);
            else rotate(y, k);
        }
        rotate(x, k);
    }
}
 
int find(int k, int rank) {
    pushdown(k);
    int l = c[k][0], r = c[k][1];
    if (sz[l] + 1 == rank) return k;
    else if (sz[l] >= rank) return find(l, rank);
    else return find(r, rank - sz[l] - 1);
}
 
void reverse(int l, int r) {
    int x = find(rt, l), y = find(rt, r + 2);
    splay(x, rt); splay(y, c[x][1]);
    int z = c[y][0];
    rev[z] ^= 1;
}
 
int findMin() {
    int x = rt;
    while (1) {
        if (v[x] < mi[c[x][0]] && v[x] < mi[c[x][1]])break;
        x = mi[c[x][0]] < mi[c[x][1]] ? c[x][0] : c[x][1];
        pushdown(x);
    }
    splay(x, rt);
    return x;
}
 
int main() {
    scanf("%d", &n);
    mi[0] = v[0] = v[1] = v[n + 2] = inf;
    for (int i = 2; i <= n + 1; ++i) scanf("%lld", v + i), v[i] = v[i] * n + i;
    build(1, n + 2, 0); rt = (n + 3) >> 1;
    for (int i = 1; i < n; ++i) {
        int x = findMin(), y = sz[c[x][0]];
        printf("%d ", y);
        v[x] = inf;
        pushup(x);
        reverse(i, y);
    }
    printf("%d\n", n);
    return 0;
}