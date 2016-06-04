/**************************************************************
    Problem: 3224
    User: syswow128
    Language: C++
    Result: Accepted
    Time:656 ms
    Memory:3148 kb
****************************************************************/
 
#include<cstdio>
 
#define LC(x) c[x][0]
#define RC(x) c[x][1]
 
const int N = 1e5 + 5;
 
int fa[N], c[N][2], root, cnt;
 
int ct[N], sz[N], num[N];
 
void newNode(int& id, int f, int v) {
    id = ++cnt;
    ct[id] = sz[id] = 1;
    LC(id) = RC(id) = 0;
    num[id] = v;
    fa[id] = f;
}
 
void update(int x) {
    sz[x] = sz[LC(x)] + sz[RC(x)] + ct[x];
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
 
void splay(int x, int &k)
{
    while (x != k)
    {
        int y = fa[x], z = fa[y];
        if (y != k)
        {
            if (c[y][0] == x^c[z][0] == y)rotate(x, k);
            else rotate(y, k);
        }
        rotate(x, k);
    }
}
 
void insert(const int v) {
    if (root == 0) {
        newNode(root, 0, v);
        return;
    }
    int x = root, y;
    while (x > 0 && num[x] != v)
        y = x, x = c[x][v > num[x]];
    if (x > 0 && num[x] == v) {
        splay(x, root);
        ++sz[x]; ++ct[x];
        return;
    }
    newNode(x, y, v);
    c[y][v > num[y]] = x;
    splay(x, root);
}
 
void erase(const int v) {
    if (root == 0) return;
    int x = root, y;
    while (x > 0 && num[x] != v)
        y = x, x = c[x][v > num[x]];
    if (x == 0 || num[x] != v)return;
    splay(x, root);
    --sz[x]; --ct[x];
    if (ct[x] > 0) return;
    if (c[x][0] == 0 && c[x][1] == 0) {
        root = 0;
        return;
    }
    int w = c[x][0] > 0;
    y = c[x][w ^ 1];
    while (c[y][w] > 0) y = c[y][w];
    splay(y, c[x][w ^ 1]);
    root = y;
    c[y][w] = c[x][w];
    fa[c[x][w]] = y;
    update(y);
}
 
void dump(int x) {
    if (x == 0)return;
    dump(LC(x));
    printf("%d : %d @ %d\n", num[x], ct[x], sz[x]);
    dump(RC(x));
}
 
int getrank(int v) {
    int x = root;
    while (x > 0 && num[x] != v)
        x = c[x][v > num[x]];
    splay(x, root);
    return 1 + (c[x][0] == 0 ? 0 : sz[c[x][0]]);
}
 
int getnum(int v) {
    int x = root;
    while (v > 0) {
        if (v > sz[LC(x)] && v <= sz[LC(x)] + ct[x]) return num[x];
        if (v <= sz[LC(x)])x = LC(x);
        else { v -= sz[LC(x)] + ct[x]; x = RC(x); }
    }
}
 
int left(int v) {
    insert(v);
    int x = c[root][0];
    while (c[x][1] > 0) {
        x = c[x][1];
    }
    erase(v);
    return num[x];
}
 
int right(int v) {
    insert(v);
    int x = c[root][1];
    while (c[x][0] > 0) {
        x = c[x][0];
    }
    erase(v);
    return num[x];
}
 
int main() {
    int n, op, x;
    scanf("%d", &n);
    while (n--) {
        scanf("%d%d", &op, &x);
        if (op == 1) {
            insert(x);
        }
        else if (op == 2) {
            erase(x);
        }
        else if (op == 3) {
            printf("%d\n", getrank(x));
        }
        else if (op == 4) {
            printf("%d\n", getnum(x));
        }
        else if (op == 5) {
            printf("%d\n", left(x));
        }
        else if (op == 6) {
            printf("%d\n", right(x));
        }
    }
    return 0;
}