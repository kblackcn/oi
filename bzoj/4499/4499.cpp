/**************************************************************
    Problem: 4499
    User: syswow64
    Language: C++
    Result: Accepted
    Time:6456 ms
    Memory:16432 kb
****************************************************************/
 
#include<cstdio>
 
typedef long long ll;
 
const int N = 5e5 + 5;
const int P = 1e9 + 7;
 
int ct = 0;
 
int lx[N], rx[N];
int lc[N], rc[N];
ll vk[N], vb[N];
 
void update(const int p) {
    vb[p] = (vb[rc[p]] + vk[rc[p]] * vb[lc[p]]) % P;
    vk[p] = (vk[rc[p]] * vk[lc[p]]) % P;
}
 
void build(int& p, const int l, const int r) {
    p = ++ct;
    lx[p] = l;
    rx[p] = r;
    if (l == r) {
        scanf("%d%d", vk + p, vb + p);
        return;
    }
    int mid = (l + r) >> 1;
    build(lc[p], l, mid);
    build(rc[p], mid + 1, r);
    update(p);
}
 
void modify(const int p, const int pos, const int k, const int b) {
    if (lx[p] == rx[p] && lx[p]==pos) {
        vk[p] = k;
        vb[p] = b;
        return;
    }
    if (pos <= rx[lc[p]])
        modify(lc[p], pos, k, b);
    else
        modify(rc[p], pos, k, b);
    update(p);
}
 
void query(const int p, const int l, const int r, ll& ans) {
    if (l <= lx[p] && rx[p] <= r) {
        ans = (ans*vk[p] + vb[p]) % P;
        return;
    }
    int mid = (l + r) >> 1;
    if (l <= rx[lc[p]])query(lc[p], l, r, ans);
    if (r >= lx[rc[p]])query(rc[p], l, r, ans);
}
 
int main() {
    int n, m, root, l, r, v;
    char ch;
    scanf("%d%d", &n, &m);
    build(root, 1, n);
    while (m-- > 0) {
        do {
            ch = getchar();
        } while ((ch != 'M') && (ch != 'Q'));
        scanf("%d %d %d", &l, &r, &v);
        if (ch == 'M') {
            modify(root, l, r, v);
        }
        else {
            ll ans = v;
            query(root, l, r, ans);
            printf("%lld\n", ans);
        }
    }
}