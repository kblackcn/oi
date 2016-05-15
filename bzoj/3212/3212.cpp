/**************************************************************
    Problem: 3212
    User: qwerty123456
    Language: C++
    Result: Accepted
    Time:40 ms
    Memory:3932 kb
****************************************************************/
 
#include<cstdio>
 
typedef long long ll;
 
const ll N = 1e5 + 5;
 
int n, q;
ll A[N], S[N], B[N], C[N];
 
void ADD_B(int x, ll c)
{
    for (int i = x; i > 0; i -= i&(-i)) B[i] += c;
}
void ADD_C(int x, ll c)
{
    for (int i = x; i <= n; i += i&(-i)) C[i] += x * c;
}
ll SUM_B(int x)
{
    ll s = 0;
    for (int i = x; i <= n; i += i&(-i)) s += B[i];
    return s;
}
ll SUM_C(int x)
{
    ll s = 0;
    for (int i = x; i > 0; i -= i&(-i)) s += C[i];
    return s;
}
inline ll SUM(int x)
{
    if (x) return SUM_B(x) * x + SUM_C(x - 1); else return 0;
}
 
inline void add(int l, int r, ll c) {
    ADD_B(r, c); ADD_C(r, c);
    if (l > 1) { ADD_B(l - 1, -c); ADD_C(l - 1, -c); }
}
 
int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", A + i);
    for (int i = n; i > 0; --i)
        add(1, i, A[i] - A[i + 1]);
    while (q-- > 0) {
        char op[5];
        int x, y, z;
        scanf("%s", op);
        if (op[0] == 'Q') {
            scanf("%d%d", &x, &y);
            printf("%lld\n", SUM(y) - SUM(x - 1));
        }
        else {
            scanf("%d%d%d", &x, &y, &z);
            add(x, y, z);
        }
    }
    return 0;
}