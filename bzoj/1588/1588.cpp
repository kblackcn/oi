/**************************************************************
    Problem: 1588
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:192 ms
    Memory:2368 kb
****************************************************************/
 
#include<cstdio>
 
const int N = 100005;
 
int min(int x, int y) { return x > y ? y : x; }
 
int fa[N], c[N][2], ct;
int v[N], root;
 
void rotate(int x, int &k) {
    int y = fa[x], z = fa[y], l, r;
    if (c[y][0] == x) l = 0; else l = 1; r = l ^ 1;
    if (y == k) k = x;
    else { if (c[z][0] == y) c[z][0] = x; else c[z][1] = x; }
    fa[x] = z; fa[y] = x; fa[c[x][r]] = y;
    c[y][l] = c[x][r]; c[x][r] = y;
}
 
void splay(int x, int&k) {
    while (x != k) {
        if (fa[x] != k) {
            int y = fa[x], z = fa[y];
            if (x == c[y][0] ^ y == c[z][0]) rotate(x, k);
            else rotate(y, k);
        }
        rotate(x, k);
    }
}
 
int nearest() {
    int ans = 1e9;
    if (c[root][0]) {
        int x = c[root][0];
        while (c[x][1] > 0) x = c[x][1];
        //splay(x, c[root][0]);
        if (v[root] - v[x] < ans) ans = v[root] - v[x];
    }
    if (c[root][1]) {
        int x = c[root][1];
        while (c[x][0] > 0) x = c[x][0];
        //splay(x, c[root][1]);
        if (v[x] - v[root] < ans) ans = v[x] - v[root];
    }
    return ans;
}
 
int insert(int x) {
    int p = root;
    bool exist = true;
    while (v[p] != x) {
        if (c[p][x > v[p]] == 0) {
            c[p][x > v[p]] = ++ct;
            fa[ct] = p;
            v[ct] = x;
            exist = false;
        }
        p = c[p][x > v[p]];
    }
    splay(p, root);
    return exist ? 0 : nearest();
}
 
int main() {
    int n, x, ans;
    scanf("%d%d", &n, &x);
    ans = v[root = ct = 1] = x;
    while (n-- > 1) {
        scanf("%d", &x);
        ans += insert(x);
    }
    printf("%d\n", ans);
    return 0;
}