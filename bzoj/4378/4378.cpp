/**************************************************************
    Problem: 4378
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:11936 ms
    Memory:43776 kb
****************************************************************/
 
#include<cstdio>
#include<algorithm>
#include<map>
 
using namespace std;
 
typedef long long ll;
 
const int N = 1e6 + 5;
const char* TAK = "TAK";
const char* NIE = "NIE";
 
struct BIT {
    ll a[N];
 
    void add(int x, ll v) {
        x += 2;
        do {
            a[x] += v;
            x = (x << 1) - (x &(x - 1));
        } while (x < N);
    }
 
    ll sum(int x) {
        x += 2;
        ll ret = 0;
        do {
            ret += a[x];
            x = x&(x - 1);
        } while (x > 0);
        return ret;
    }
} X, Y;
 
struct OP {
    bool t;
    int a, b, c;
} seq[N];
 
int n, m;
 
char op[2];
 
int a[N], b[N], c[N];
 
int find(int x) {
    return lower_bound(a, a + m, x) - a;
}
 
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) b[i] = -1, c[i] = 0;
    for (int i = 0; i < m; ++i) {
        scanf("%s%d%d", &op, &seq[i].a, &seq[i].b);
        seq[i].t = op[0] == 'U';
        if (seq[i].t) --seq[i].a;
        a[i] = seq[i].b;
    }
    sort(a, a + m);
    for (int i = 0; i < m; ++i) seq[i].c = find(seq[i].b);
    X.add(-1, n);
    for (int i = 0; i < m; ++i)if (seq[i].t) {
        int j = seq[i].a;
        X.add(b[j], -1);
        Y.add(b[j], -c[j]);
        b[j] = seq[i].c; c[j] = seq[i].b;
        X.add(b[j], 1);
        Y.add(b[j], c[j]);
    }
    else {
        int x = n - X.sum(seq[i].c - 1);
        if (x >= seq[i].a) {
            puts(TAK); continue;
        }
        ll y = ((ll)seq[i].a - x)*seq[i].b;
        if (Y.sum(seq[i].c - 1) >= y)puts(TAK); else puts(NIE);
    }
    return 0;
}