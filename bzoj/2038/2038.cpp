/**************************************************************
    Problem: 2038
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:1372 ms
    Memory:2972 kb
****************************************************************/
 
#include<cstdio>
#include<cmath>
#include<algorithm>
 
typedef long long ll;
 
const int N = 5e4 + 5;
const int M = 5e4 + 5;
 
struct q {
    int l, r;
};
 
q qs[M];
int rk[M], clr[N], bp[N];
 
ll ansA[N], ansB[N], cnt[N];
 
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a%b); }
 
bool cmpX(const q& x, const q& y) {
    return bp[x.l] == bp[y.l] ? x.r < y.r : x.l < y.l;
}
 
bool cmp(int x, int y) { return cmpX(qs[x], qs[y]); }
 
ll cur = 0;
 
void update(int pos, int v) {
    pos = clr[pos];
    cur -= cnt[pos] * cnt[pos];
    cnt[pos] += v;
    cur += cnt[pos] * cnt[pos];
}
 
int main() {
    int n, m, blk;
    scanf("%d%d", &n, &m);
    blk = (int)sqrt(n);
    for (int i = 1; i <= n; ++i)scanf("%d", clr + i);
    for (int i = 1; i <= n; ++i) bp[i] = (i - 1) / blk;
    for (int i = 0; i < m; ++i)
        scanf("%d%d", &qs[i].l, &qs[i].r), rk[i] = i;
    std::sort(rk, rk + m, cmp);
    int l = 1, r = 0;
    for (int pp = 0; pp < m; ++pp) {
        int i = rk[pp];
        for (; r < qs[i].r; r++)
            update(r + 1, 1);
        for (; r > qs[i].r; r--)
            update(r, -1);
        for (; l < qs[i].l; l++)
            update(l, -1);
        for (; l > qs[i].l; l--)
            update(l - 1, 1);
        ansA[i] = cur - (qs[i].r - qs[i].l + 1);
        ansB[i] = (ll)(qs[i].r - qs[i].l + 1)*(qs[i].r - qs[i].l);
        ll k = gcd(ansA[i], ansB[i]);
        ansA[i] /= k; ansB[i] /= k;
    }
    for (int i = 0; i < m; ++i) {
        printf("%lld/%lld\n", ansA[i], ansB[i]);
    }
    return 0;
}