/**************************************************************
    Problem: 2875
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:44 ms
    Memory:1272 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
 
using namespace std;
 
typedef long long ll;
 
ll m, a, c, x0, n, g;
 
ll mu(ll x, ll y) {
    ll ret = 0;
    while (y > 0) {
        if (y & 1) ret = (ret + x) % m;
        x = (x << 1) % m;
        y >>= 1;
    }
    return ret;
}
 
int main() {
    cin >> m >> a >> c >> x0 >> n >> g;
    ll t0 = a, t1 = c;
    ll ans = x0;
    while (n > 0) {
        if (n & 1) ans = (mu(ans, t0) + t1) % m;
        t1 = (t1 + mu(t0, t1)) % m;
        t0 = mu(t0, t0);
        n >>= 1;
    }
    cout << ans%g << endl;
    return 0;
}