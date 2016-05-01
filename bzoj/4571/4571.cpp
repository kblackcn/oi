/**************************************************************
    Problem: 4571
    User: shzhw
    Language: C++
    Result: Accepted
    Time:18876 ms
    Memory:95336 kb
****************************************************************/
 
#include<cstdio>
#include<algorithm>
 
using namespace std;
 
const int MX = 1e5 - 1;
 
const int N = 2e5 + 5;
const int M = 8e6;
 
int root[N];
 
int dat[M], lc[M], rc[M], ct;
 
int cmpNode(const int x) {
    dat[++ct] = dat[x], lc[ct] = lc[x], rc[ct] = rc[x];
    return ct;
}
 
void add(int& now, const int old, const int l, const int r, const int v) {
    now = cmpNode(old);
    if (l == r) {
        ++dat[now];
        return;
    }
    int mid = (l + r) >> 1;
    if (v <= mid) add(lc[now], lc[old], l, mid, v);
    else add(rc[now], rc[old], mid + 1, r, v);
    dat[now] = dat[lc[now]] + dat[rc[now]];
}
 
int query(const int left, const int right, const int l, const int r, const int ql, const int qr) {
    if (dat[right] - dat[left] == 0)return 0;
    if (ql <= l && r <= qr) {
        return dat[right] - dat[left];
    }
    int mid = (l + r) >> 1;
    int ret = 0;
    if (ql <= mid) ret += query(lc[left], lc[right], l, mid, ql, qr);
    if (qr > mid) ret += query(rc[left], rc[right], mid + 1, r, ql, qr);
    return ret;
}
 
int ok(const int x) {
    if (x < 0) return 0;
    if (x > MX) return MX;
    return x;
}
 
int main() {
    int n, m, x;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &x);
        add(root[i], root[i - 1], 0, MX, x);
    }
    for (int i = 1; i <= m; ++i) {
        int b, x, l, r;
        scanf("%d%d%d%d", &b, &x, &l, &r);
        int lb = 0;
        --l;
        for (int j = (1 << 17); j > 0; j >>= 1) {
            if ((b & j) > 0) {
                if (lb + j - x - 1 >= 0) {
                    if (query(root[l], root[r], 0, MX, ok(lb - x), ok(lb + j - x - 1)) == 0)
                        lb += j;
                }
                else { lb += j; }
            }
            else {
                if (lb + j - x <= MX) {
                    if (query(root[l], root[r], 0, MX, ok(lb + j - x), ok(lb + j * 2 - x - 1)) == 0);
                    else lb += j;
                }
            }
        }
        printf("%d\n", lb ^ b);
    }
    return 0;
}