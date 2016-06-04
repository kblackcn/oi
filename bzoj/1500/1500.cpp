/**************************************************************
    Problem: 1500
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:4144 ms
    Memory:26572 kb
****************************************************************/
 
#include<cstdio>
#include<cctype>
#include<queue>
 
#define NOFILL -1001
 
#define inf 1000000000
 
#define LC(x) c[x][0]
#define RC(x) c[x][1]
#define LD(x) d[LC(x)]
#define RD(x) d[RC(x)]
#define LT(x) t[LC(x)]
#define RT(x) t[RC(x)]
 
const int N = 5e5 + 5;
 
void read(int& x) {
    x = 0;
    static char ch;
    static int f;
    f = 1;
    while (!isdigit(ch = getchar()))if (ch == '-') f = -1;
    do { x = x * 10 + ch - 48; } while (isdigit(ch = getchar()));
    x *= f;
}
 
int max(int x, int y) { return x > y ? x : y; }
 
void up(int &x, int y) { if (y > x) x = y; }
 
void swap(int &x, int &y) { int t = x; x = y; y = t; }
 
int fa[N], c[N][2], v[N], sz[N];
struct Data {
    int s, l, r, m;
    Data() {}
    Data(int s, int l, int r, int m) :s(s), l(l), r(r), m(m) {}
} d[N];
struct Tag {
    bool r;
    int f;
    Tag() {}
    Tag(bool r, int f) :r(r), f(f) {}
} t[N];
 
void update(int x) {
    if (x == 0)return;
    sz[x] = sz[LC(x)] + 1 + sz[RC(x)];
    d[x].s = LD(x).s + v[x] + RD(x).s;
    d[x].l = max(LD(x).l, LD(x).s + v[x] + RD(x).l);
    d[x].r = max(RD(x).r, RD(x).s + v[x] + LD(x).r);
    d[x].m = max(max(LD(x).m, RD(x).m), LD(x).r + v[x] + RD(x).l);
}
 
void tagFill(int x, int f) {
    if (x == 0)return;
    t[x].f = v[x] = f;
    t[x].r = false;
    if (f >= 0) {
        int s = f*sz[x];
        d[x] = Data(f*sz[x], s, s, s);
    }
    else {
        d[x] = Data(f*sz[x], 0, 0, f);
    }
}
 
void tagRev(int x) {
    if (t[x].f != NOFILL)return;
    t[x].r ^= 1;
    swap(d[x].l, d[x].r);
    swap(LC(x), RC(x));
}
 
 
void push(int x) {
    if (t[x].f != NOFILL) {
        int f = t[x].f;
        t[x].f = NOFILL;
        tagFill(LC(x), f);
        tagFill(RC(x), f);
    }
    if (t[x].r) {
        t[x].r = false;
        tagRev(LC(x));
        tagRev(RC(x));
    }
}
 
void rotate(int x, int &k)
{
    int y = fa[x], z = fa[y], l, r;
    l = (c[y][1] == x); r = l ^ 1;
    if (y == k)k = x;
    else c[z][c[z][1] == y] = x;
    fa[c[x][r]] = y; fa[y] = x; fa[x] = z;
    c[y][l] = c[x][r]; c[x][r] = y;
    update(y); update(x);
}
 
void splay(int x, int& rt) {
    while (x != rt) {
        if (fa[x] != rt) {
            int y = fa[x], z = fa[y];
            if (c[y][0] == x ^ c[z][0] == y) rotate(x, rt);
            else rotate(y, rt);
        }
        rotate(x, rt);
    }
}
 
int find(int x, int r) {
    while (1) {
        push(x);
        if (r == sz[LC(x)] + 1)return x;
        if (r <= sz[LC(x)]) x = LC(x); else {
            r -= sz[LC(x)] + 1;
            x = RC(x);
        }
    }
}
 
namespace ID {
    std::queue<int> ava;
    int ct = 0;
 
    void gi(int& x) {
        if (ava.empty())x = ++ct;
        else x = ava.front(), ava.pop();
    }
 
    void ri(int& x) { ava.push(x); }
 
    void rcl(int x) {
        if (x == 0)return;
        rcl(LC(x));
        ri(x);
        rcl(RC(x));
    }
}
 
namespace Builder {
 
    int a[N];
    int b[N];
 
    void build(int& x, int l, int r, int f) {
        if (l > r) {
            x = 0;
            return;
        }
        if (l == r) {
            x = b[l];
            if (a[l] >= 0) d[x] = Data(a[l], a[l], a[l], a[l]);
            else d[x] = Data(a[l], 0, 0, a[l]);
            v[x] = a[l];
            t[x] = Tag(false, NOFILL);
            fa[x] = f;
            c[x][0] = c[x][1] = 0;
            sz[x] = 1;
            return;
        }
        int mid = (l + r) >> 1;
        x = b[mid];
        if (a[mid] > 0) d[x] = Data(a[mid], a[mid], a[mid], a[mid]);
        else d[x] = Data(a[mid], 0, 0, a[mid]);
        v[x] = a[mid];
        t[x] = Tag(false, NOFILL);
        fa[x] = f;
        sz[x] = 1;
        build(c[x][0], l, mid - 1, x);
        build(c[x][1], mid + 1, r, x);
        update(x);
    }
 
    int build(const int c) {
        for (int i = 1; i <= c; ++i) read(a[i]), ID::gi(b[i]);
        int ret;
        build(ret, 1, c, 0);
        return ret;
    }
 
    int initBuild(const int c) {
        d[0].m = -inf;
        for (int i = 1; i <= c + 2; ++i) ID::gi(b[i]);
        a[1] = a[c + 2] = -inf;
        for (int i = 1; i <= c; ++i) read(a[i + 1]);
        int ret;
        build(ret, 1, c + 2, 0);
        return ret;
    }
}
 
char op[20];
 
int main() {
    int n, m, p, q, r, root;
    read(n); read(m);
    root = Builder::initBuild(n);
    while (m--) {
        scanf("%s", op);
        if (op[0] == 'M' && op[4] == 'S') {
            printf("%d\n", d[root].m);
            continue;
        }
        if (op[0] == 'I') {
            read(p); read(q);
            int x = find(root, p + 1), y = find(root, p + 2);
            int z = Builder::build(q);
            splay(x, root); splay(y, c[x][1]);
            fa[z] = y, c[y][0] = z;
            update(y); update(x);
            continue;
        }
        if (op[0] == 'D') {
            read(p); read(q);
            int x = find(root, p), y = find(root, p + q + 1);
            splay(x, root); splay(y, c[x][1]);
            ID::rcl(c[y][0]);
            c[y][0] = 0;
            update(y); update(x);
        }
 
        if (op[0] == 'M') {
            read(p); read(q); read(r);
            int x = find(root, p), y = find(root, p + q + 1);
            splay(x, root); splay(y, c[x][1]);
            tagFill(c[y][0], r);
            update(y); update(x);
 
        }
 
        if (op[0] == 'R') {
            read(p); read(q);
            int x = find(root, p), y = find(root, p + q + 1);
            splay(x, root); splay(y, c[x][1]);
            tagRev(c[y][0]);
            update(y); update(x);
 
        }
 
        if (op[0] == 'G') {
            read(p); read(q);
            int x = find(root, p), y = find(root, p + q + 1);
            splay(x, root); splay(y, c[x][1]);
            printf("%d\n", d[c[y][0]].s);
        }
    }
    return 0;
}