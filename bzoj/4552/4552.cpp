/**************************************************************
    Problem: 4552
    User: shzhw
    Language: C++
    Result: Accepted
    Time:9244 ms
    Memory:9804 kb
****************************************************************/
 
#include<cstdio>
 
#define lc(x) d[x].lc
#define rc(x) d[x].rc
 
#define ld(x) d[x]
#define rd(x) d[x]
 
const int N = 1e5 + 5;
const int M = N * 3;
 
int V[N], Origin[N];
 
struct SegmentTree {
private:
    struct data {
        int lc, rc;
        int lb, rb;
        int sum, tag;
    } d[M];
    int ct, bl, br, root;
    int ql, qr, op;
 
    void tag(const int p, const int op) {
        d[p].tag = op;
        d[p].sum = op*(d[p].rb - d[p].lb + 1);
    }
 
    void down(const int p) {
        if (d[p].tag == -1) return;
        if (lc(p) != 0) {
            tag(lc(p), d[p].tag);
            tag(rc(p), d[p].tag);
        }
        d[p].tag = -1;
    }
 
    void up(const int p) {
        d[p].sum = d[lc(p)].sum + d[rc(p)].sum;
    }
 
    void build(int& p, const int l, const int r) {
        p = ++ct;
        d[p].lb = l; d[p].rb = r; d[p].tag = -1;
        if (l == r) {
            d[p].sum = V[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(d[p].lc, l, mid);
        build(d[p].rc, mid + 1, r);
        up(p);
    }
 
    void refresh(const int p, const int l, const int r) {
        d[p].tag = -1;
        if (l == r) {
            d[p].sum = V[l];
            return;
        }
        int mid = (l + r) >> 1;
        refresh(d[p].lc, l, mid);
        refresh(d[p].rc, mid + 1, r);
        up(p);
    }
 
    int sum(const int p) {
        if (ql <= d[p].lb && d[p].rb <= qr) {
            return d[p].sum;
        }
        int ret = 0;
        down(p);
        if (ql <= d[lc(p)].rb)ret += sum(lc(p));
        if (qr >= d[rc(p)].lb)ret += sum(rc(p));
        return ret;
    }
 
    void set(const int p) {
        if (ql <= d[p].lb && d[p].rb <= qr) {
            tag(p, op);
            return;
        }
        down(p);
        if (ql <= d[lc(p)].rb) set(lc(p));
        if (qr >= d[rc(p)].lb) set(rc(p));
        up(p);
    }
 
public:
    void build(int l, int r) {
        ct = 0;
        bl = l; br = r;
        build(root, bl, br);
    }
 
    void refresh() {
        refresh(root, bl, br);
    }
 
    int sum(int l, int r) {
        if (l > r)return 0;
        ql = l; qr = r;
        return sum(root);
    }
 
    void set(int l, int r, int o) {
        if (l > r)return;
        ql = l; qr = r; op = o;
        set(root);
    }
} st;
 
struct Operation {
    int op, l, r;
} x[N];
 
int n, m, Q;
 
bool check(int bd) {
    for (int i = 1; i <= n; ++i) V[i] = Origin[i] > bd ? 1 : 0;
    st.refresh();
    for (int i = 1; i <= m; ++i) {
        int op = x[i].op, l = x[i].l, r = x[i].r;
        int cnt = st.sum(l, r);
        if (op == 0) {
            st.set(l, r - cnt, 0);
            st.set(r - cnt + 1, r, 1);
        }
        else {
            st.set(l, l + cnt - 1, 1);
            st.set(l + cnt, r, 0);
        }
    }
    return st.sum(Q, Q);
}
 
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%d", Origin + i);
    for (int i = 1; i <= m; ++i)scanf("%d%d%d", &x[i].op, &x[i].l, &x[i].r);
    scanf("%d", &Q);
    int l = 1; int r = n;
    st.build(1, n);
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) l = mid + 1; else r = mid;
    }
    printf("%d\n", l);
    return 0;
}