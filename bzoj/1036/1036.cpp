/**************************************************************
    Problem: 1036
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:2484 ms
    Memory:5784 kb
****************************************************************/
 
#include<cstdio>
 
const int N = 3e4 + 5;
const int M = N * 2;
 
int head[N], next[M], tar[M], ct;
 
void insert(int u, int v) {
    next[++ct] = head[u]; tar[ct] = v; head[u] = ct;
}
 
int w[N], tw[N];
 
int _max(int x, int y) { return x > y ? x : y; }
 
struct SegmentTreeBuilder {
    struct Data {
        Data *lc, *rc;
        int lb, rb, sum, max;
    } dat[M];
    int ct;
 
    struct SegmentTree {
    private:
 
        void update(Data* &p) {
            p->sum = p->lc->sum + p->rc->sum;
            p->max = _max(p->lc->max, p->rc->max);
        }
 
        void build(Data* &p, int l, int r) {
            p = builder->newnode();
            p->lb = l; p->rb = r;
            if (l == r) {
                p->max = p->sum = tw[l];
                return;
            }
            int mid = (l + r) >> 1;
            build(p->lc, l, mid);
            build(p->rc, mid + 1, r);
            update(p);
        }
 
        int query_max(Data* &p, int l, int r) {
            if (l <= p->lb && p->rb <= r) {
                return p->max;
            }
            int ans = -30001;
            if (l <= p->lc->rb) ans = query_max(p->lc, l, r);
            if (r >= p->rc->lb) ans = _max(ans, query_max(p->rc, l, r));
            return ans;
        }
 
        int query_sum(Data* &p, int l, int r) {
            if (l <= p->lb && p->rb <= r) {
                return p->sum;
            }
            int ans = 0;
            if (l <= p->lc->rb) ans += query_sum(p->lc, l, r);
            if (r >= p->rc->lb) ans += query_sum(p->rc, l, r);
            return ans;
        }
 
        void update(Data* &p, int pos, int v) {
            if (pos == p->lb && pos == p->rb) {
                p->sum = p->max = v;
                return;
            }
            int ans = 0;
            if (pos <= p->lc->rb) update(p->lc, pos, v);
            else update(p->rc, pos, v);
            update(p);
        }
 
        SegmentTreeBuilder* builder;
        Data* root;
 
    public:
        SegmentTree(SegmentTreeBuilder* builder, int l, int r) {
            this->builder = builder;
            this->build(root, l, r);
        }
 
        int query_max(int l, int r) {
            if (l > r) {
                int t = l; l = r; r = t;
            }
            return this->query_max(root, l, r);
        }
 
        int query_sum(int l, int r) {
            if (l > r) {
                int t = l; l = r; r = t;
            }
            return this->query_sum(root, l, r);
        }
 
        void change(int x, int y) {
            update(root, x, y);
        }
 
    };
 
    Data* newnode() {
        return dat + ct++;
    }
 
    SegmentTree* build(int l, int r) {
        return new SegmentTree(this, l, r);
    }
} builder;
 
int par[N], top[N], last[N], size[N], dep[N], hav[N], pos[N], cp = 0;
 
void dfs(int p) {
    size[p] = 1;
    int mx = 0;
    for (int i = head[p]; i > 0; i = next[i]) {
        int  j = tar[i];
        if (j == par[p])continue;
        par[j] = p;
        dep[j] = dep[p] + 1;
        dfs(j);
        size[p] += size[j];
        if (size[j] > mx) {
            mx = size[j];
            hav[p] = j;
        }
    }
}
 
void work(int p) {
    pos[p] = ++cp;
    tw[cp] = w[p];
    last[top[p]] = p;
    if (hav[p] != 0) {
        top[hav[p]] = top[p];
        work(hav[p]);
    }
    for (int i = head[p]; i > 0; i = next[i]) {
        int  j = tar[i];
        if (j == par[p] || j == hav[p])continue;
        top[j] = j;
        work(j);
    }
}
 
SegmentTreeBuilder::SegmentTree *st[N];
 
int query_max(int x, int y) {
    int ans = -30001;
    while (1)
    {
        if (top[x] == top[y])
            return _max(ans, st[top[x]]->query_max(pos[x], pos[y]));
        else if (dep[top[x]] >= dep[top[y]])
            ans = _max(ans, st[top[x]]->query_max(pos[x], pos[top[x]])), x = par[top[x]];
        else ans = _max(ans, st[top[y]]->query_max(pos[y], pos[top[y]])), y = par[top[y]];
    }
}
 
int query_sum(int x, int y) {
    int ans = 0;
    while (1)
    {
        if (top[x] == top[y])
            return ans + st[top[x]]->query_sum(pos[x], pos[y]);
        else if (dep[top[x]] >= dep[top[y]])
            ans += st[top[x]]->query_sum(pos[x], pos[top[x]]), x = par[top[x]];
        else ans += st[top[y]]->query_sum(pos[y], pos[top[y]]), y = par[top[y]];
    }
}
 
 
int main() {
    int n, q, x, y;
    char query[10];
 
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        insert(u, v);
        insert(v, u);
    }
    for (int i = 1; i <= n; ++i)scanf("%d", w + i);
 
    dep[1] = 0;
    dfs(1);
    top[1] = 1;
    work(1);
 
    for (int i = 1; i <= n; ++i) {
        if (st[top[i]] == NULL) {
            st[top[i]] = builder.build(pos[top[i]], pos[last[top[i]]]);
        }
    }
 
    scanf("%d", &q);
    while (q-- > 0) {
        scanf("%s%d%d", query, &x, &y);
        if (query[1] == 'M') {
            printf("%d\n", query_max(x, y));
        }
        else if (query[1] == 'S') {
            printf("%d\n", query_sum(x, y));
        }
        else {
            st[top[x]]->change(pos[x], y);
        }
    }
    return 0;
}