/**************************************************************
    Problem: 4458
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:15752 ms
    Memory:135344 kb
****************************************************************/
 
#include <cstdio>
#include <vector>
#include <queue>
 
using namespace std;
 
const int N = 5e5 + 5;
 
int fa[N][20];
int dep[N];
int a[N][20];
int ap[N][20];
 
struct node {
    int l, r, id, idx, v;
};
 
struct cmp {
    bool operator() (const node &a, const node &b)
    {
        return a.v < b.v;
    }
};
 
priority_queue<node, vector<node>, cmp> pq;
 
int query(int id, int l, int r) {
    int x = id;
    if (dep[x] > r)
        for (int k = 19; k >= 0; --k)
            if (dep[x] - (1 << k) >= r)
                x = fa[x][k];
    --l;
    int ansV = 1e9, ansP = -1;
    for (int k = 19; k >= 0; --k)
        if (dep[x] - (1 << k) >= l) {
            if (ansV > a[x][k]) {
                ansV = a[x][k];
                ansP = ap[x][k];
            }
            x = fa[x][k];
        }
    return ansP;
}
 
void insertNode(int id, int l, int r) {
    if (l > r) return;
    int mid = query(id, l, r);
    int v = a[id][0] - a[mid][0];
    node x;
    x.l = l; x.r = r; x.id = id; x.idx = mid; x.v = v;
    pq.push(x);
}
 
int main() {
    int n, m, l, r;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) scanf("%d", fa[i] + 0);
    for (int i = 1; i <= n; ++i) scanf("%d", a[i] + 0), dep[i] = dep[fa[i][0]] + 1, a[i][0] += a[fa[i][0]][0], ap[i][0] = i;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < 20; ++j) {
            int fx = fa[i][j - 1];
            fa[i][j] = fa[fx][j - 1];
            a[i][j] = a[i][j - 1];
            ap[i][j] = ap[i][j - 1];
            if (a[fx][j - 1] < a[i][j]) {
                a[i][j] = a[fx][j - 1];
                ap[i][j] = ap[fx][j - 1];
            }
        }
    scanf("%d%d%d", &m, &l, &r);
    long long ans = 0;
    for (int i = 1; i <= n; ++i) if (dep[i] >= l) insertNode(i, max(dep[i] - r, 0), dep[i] - l);
    while (m-- > 0) {
        node cur = pq.top(); pq.pop();
        ans += cur.v;
        insertNode(cur.id, cur.l, dep[cur.idx] - 1);
        insertNode(cur.id, dep[cur.idx] + 1, cur.r);
    }
    printf("%lld\n", ans);
    return 0;
}