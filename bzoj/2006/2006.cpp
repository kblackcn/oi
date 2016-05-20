/**************************************************************
    Problem: 2006
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:2088 ms
    Memory:96280 kb
****************************************************************/
 
#include<cstdio>
#include<queue>
#include<vector>
 
using namespace std;
 
const int N = 5e5+5;
 
struct node {
    int l, r, id, idx, v;
};
 
struct cmp {
    bool operator() (const node &a, const node &b)
    {
        return a.v < b.v;
    }
};
 
int n, k, L, R;
int mv[20][N];
int mp[20][N];
int a[N];
 
priority_queue<node, vector<node>, cmp> pq;
 
void buildST() {
    for(int i = 0; i<n; ++i) {
        mv[0][i] = a[i];
        mp[0][i] = i;
    }
    for(int t = 1; (1<<t) <= n; ++t) {
        for(int i = 0; i<n; ++i) {
            mv[t][i] = mv[t-1][i];
            mp[t][i] = mp[t-1][i];
            int j = i+(1 << (t-1));
            if(j<n && mv[t-1][j]>mv[t][i]) {
                mv[t][i] = mv[t-1][j];
                mp[t][i] = mp[t-1][j];
            }
        }
    }
}
 
int query(int l, int r) {
    ++r;
    int ansV = -N*1000, ansP = -1;
    for(int t = 19; t>-1; --t) if(l+(1<<t)<=r) {
        if(mv[t][l]>ansV) {
            ansV = mv[t][l];
            ansP = mp[t][l];
        }
        l+=(1<<t);
    }
    return ansP;
}
 
void insertNode(int id, int l, int r) {
    if(l>r) return;
    int mid = (l==r)?l:query(l, r);
    int v = id==0?a[mid]:a[mid] - a[id-1];
    node x;
    x.l = l; x.r = r; x.id = id; x.idx = mid; x.v = v;
    pq.push(x);
}
 
int main() {
    scanf("%d%d%d%d%d", &n, &k, &L, &R, a+0); --L; --R;
    for(int i = 1; i<n; ++i) scanf("%d", a+i), a[i] += a[i-1];
    buildST();
    for(int i = 0; i<n; ++i) if(i+L<n) insertNode(i, i+L, i+R>n-1?n-1:i+R);
    long long ans = 0;
    while(k-->0) {
        node cur = pq.top(); pq.pop();
        ans+=cur.v;
        insertNode(cur.id, cur.l, cur.idx-1);
        insertNode(cur.id, cur.idx+1, cur.r);
    }
    printf("%lld\n", ans);
    return 0;
}