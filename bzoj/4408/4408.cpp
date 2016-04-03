/**************************************************************
    Problem: 4408
    User: qwerty123456
    Language: C++
    Result: Accepted
    Time:1888 ms
    Memory:63696 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
 
const int N = 1e5 + 5;
const int NM = 4.0e6 + 5;
 
using namespace std;
 
int lc[NM], rc[NM], val[NM], root[NM];
 
int maxnum;
 
int a[N];
 
int ct = 0;
 
int lim;
 
void add(int& now, int old, int l, int r) {
    now = ++ct;
    val[now] = val[old] + lim;
    if (l == r)return;
    lc[now] = lc[old]; rc[now] = rc[old];
    int mid = (l + r) >> 1;
    if (lim > mid) {
        add(rc[now], rc[old], mid + 1, r);
    }
    else {
        add(lc[now], lc[old], l, mid);
    }
}
 
int query(const int x, const int y, int l, int r) {
    if (r <= lim)return val[y] - val[x];
    int mid = (l + r) >> 1;
    return mid < lim
        ? val[lc[y]] - val[lc[x]] + query(rc[x], rc[y], mid + 1, r)
        : query(lc[x], lc[y], l, mid);
}
 
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        if (a[i] > maxnum) maxnum = a[i];
    }
    for (int i = 0; i < n; ++i) {
        lim = a[i];
        add(root[i+1], root[i], 0, maxnum);
    }
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        int l, r;
        scanf("%d%d", &l, &r);
        int ans = 1;
        while (true) {
            lim = ans;
            int sum = query(root[l-1], root[r], 0, maxnum);
            if (sum < ans) break;
            ans = sum + 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}