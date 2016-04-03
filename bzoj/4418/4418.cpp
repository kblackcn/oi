/**************************************************************
    Problem: 4418
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:912 ms
    Memory:14608 kb
****************************************************************/
 
#include<cstdio>
#include<vector>
#include<algorithm>
#include<iostream>
 
using namespace std;
 
typedef long long ll;
 
const int N = 100005;
const int M = 1000006;
const int MS = M * 2;
 
struct par {
public:
    par(int _id, int _pos) {
        id = _id;
        pos = _pos;
    }
 
    int id, pos;
};
 
int n, m, k;
int ct;
 
int r[N];
vector<par> first, last;
 
bool cmp(const par& x, const par& y) {
    return x.pos < y.pos;
}
 
int bit[MS];
 
int lowbit(const int x) {
    return x - (x & (x - 1));
}
 
 
void push(const int id) {
    int p = r[id];
    ++ct;
    while (p < MS) {
        bit[p] += 1;
        p += lowbit(p);
    }
}
 
void pop(const int id) {
    int p = r[id];
    --ct;
    while (p < MS) {
        bit[p] -= 1;
        p += lowbit(p);
    }
}
 
ll rad() {
    if (ct < k) return 0;
    int c = 0, tar = ct - k + 1;
    for (int i = 1 << 20; i > 0; i >>= 1) {
        if (c + i < MS && bit[c + i] < tar) {
            tar -= bit[c + i];
            c += i;
        }
    }
    return c + 1;
}
 
ll sqr(const ll x) {
    return x * x;
}
 
int main() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; ++i) {
        int R, a1, a2;
        scanf("%d%d%d", &R, &a1, &a2);
        a1 += m;
        a2 += m;
        r[i] = R;
        if (a1 < a2) {
            first.push_back(par(i, a1));
            last.push_back(par(i, a2));
        }
        else {
            first.push_back(par(i, 0));
            last.push_back(par(i, a2));
            first.push_back(par(i, a1));
            last.push_back(par(i, m*2));
        }
    }
    sort(first.begin(), first.end(), cmp);
    sort(last.begin(), last.end(), cmp);
 
    vector<par>::iterator x = first.begin(), y = last.begin();
    int pos = 0;
    ll ans = 0;
    while (y != last.end()) {
        int now;
 
        if (x == first.end())
            now = y->pos;
        else
            now = min(x->pos, y->pos);
 
        int r = rad();
 
        ans += (now - pos)*sqr(r);
         
        while (y != last.end() && y->pos == now) {
            pop(y->id);
            ++y;
        }
        while (x != first.end() && x->pos == now) {
            push(x->id);
            ++x;
        }
        pos = now;
    }
    cout << ans;
    return 0;
}