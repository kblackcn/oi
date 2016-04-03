/**************************************************************
    Problem: 1858
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:3868 ms
    Memory:14092 kb
****************************************************************/
 
#include<cstdio>
 
const int N = 200005;
 
int count;
 
int max(const int a, const int b) {
    return a>b ? a : b;
}
 
int getFlag() {
    char ch;
    do {
        ch = getchar();
    } while (ch != '0' && ch != '1');
    return ch == '1';
}
 
void swap(int& x, int& y) {
    int t = x;
    x = y;
    y = t;
}
 
struct Data {
    int len;
    int count;
    int left, right;
    int longest;
} da[N], db[N];
 
struct Tag {
    int fill;
    bool reverse;
} tag[N];
 
int l[N], r[N], cap[N];
int lp[N], rp[N];
 
Data* EmptyData() {
    Data* dat = new Data();
    dat->len = dat->count = dat->left = dat->right = dat->longest = 0;
    return dat;
}
 
void reverse(const int p) {
    swap(da[p].count, db[p].count);
    swap(da[p].left, db[p].left);
    swap(da[p].right, db[p].right);
    swap(da[p].longest, db[p].longest);
}
 
void fillData(const int p, const int op) {
    if (op == 1) {
        da[p].left = da[p].right = da[p].longest = da[p].count = cap[p];
        db[p].left = db[p].right = db[p].longest = db[p].count = 0;
    }
    else {
        da[p].left = da[p].right = da[p].longest = da[p].count = 0;
        db[p].left = db[p].right = db[p].longest = db[p].count = cap[p];
    }
}
 
void tryFill(const int p, const int op) {
    tag[p].fill = op;
    tag[p].reverse = false;
    fillData(p, op);
}
 
void tryReverse(const int p) {
    if (tag[p].fill != -1) {
        fillData(p, tag[p].fill = 1 - tag[p].fill);
    }
    else {
        tag[p].reverse = !tag[p].reverse;
        reverse(p);
    }
}
 
void merge(const Data* a, const Data* b, Data* c) {
    c->len = a->len + b->len;
    c->count = a->count + b->count;
 
    c->left = a->left;
    if (c->left == a->len) {
        c->left += b->left;
    }
    c->right = b->right;
    if (c->right == b->len) {
        c->right += a->right;
    }
 
    c->longest = max(max(c->left, c->right), max(a->right + b->left, max(a->longest, b->longest)));
}
 
void down(const int p) {
    if (tag[p].fill != -1) {
        tryFill(lp[p], tag[p].fill);
        tryFill(rp[p], tag[p].fill);
        tag[p].fill = -1;
    }
    else if (tag[p].reverse) {
        tryReverse(lp[p]);
        tryReverse(rp[p]);
        tag[p].reverse = false;
    }
}
 
void update(const int p) {
    merge(da + lp[p], da + rp[p], da + p);
    merge(db + lp[p], db + rp[p], db + p);
}
 
void build(int& p, const int left, const int right) {
    p = ++count;
    l[p] = left, r[p] = right, da[p].len = db[p].len = cap[p] = right + 1 - left;
    tag[p].fill = -1;
    if (right == left) {
        int v = getFlag();
        fillData(p, v);
    }
    else {
        int mid = (left + right) >> 1;
        build(lp[p], left, mid);
        build(rp[p], mid + 1, right);
        update(p);
    }
}
 
void fill(const int p, const int left, const int right, const int op) {
    if (left>r[p] || right<l[p]) {
        return;
    }
    if (left <= l[p] && r[p] <= right) {
        tryFill(p, op);
        return;
    }
    down(p);
    fill(lp[p], left, right, op);
    fill(rp[p], left, right, op);
    update(p);
}
 
void reverse(const int p, const int left, const int right) {
    if (left>r[p] || right<l[p]) {
        return;
    }
    if (left <= l[p] && r[p] <= right) {
        tryReverse(p);
        return;
    }
    down(p);
    reverse(lp[p], left, right);
    reverse(rp[p], left, right);
    update(p);
}
 
int query(const int p, const int left, const int right) {
    if (left>r[p] || right<l[p]) {
        return 0;
    }
    if (left <= l[p] && r[p] <= right) {
        return da[p].count;
    }
    down(p);
    int ans = query(lp[p], left, right) + query(rp[p], left, right);
    update(p);
    return ans;
}
 
Data* queryMax(const int p, const int left, const int right) {
    if (left>r[p] || right<l[p]) {
        return EmptyData();
    }
    if (left <= l[p] && r[p] <= right) {
        return new Data(da[p]);
    }
    down(p);
    Data *x = queryMax(lp[p], left, right);
    Data *y = queryMax(rp[p], left, right);
    Data *v = new Data();
    merge(x, y, v);
    delete x;
    delete y;
    update(p);
    return v;
}
 
int queryMaxium(const int p, const int left, const int right) {
    Data* dat = queryMax(p, left, right);
    int ans = dat->longest;
    delete dat;
    return ans;
}
 
int main() {
    int n, m, root;
    scanf("%d%d", &n, &m);
    build(root, 0, n - 1);
    while (m-->0) {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);
        switch (op) {
        case 0:
            fill(root, x, y, 0);
            break;
        case 1:
            fill(root, x, y, 1);
            break;
        case 2:
            reverse(root, x, y);
            break;
        case 3:
            printf("%d\n", query(root, x, y));
            break;
        case 4:
            printf("%d\n", queryMaxium(root, x, y));
            break;
        }
    }
    return 0;
}