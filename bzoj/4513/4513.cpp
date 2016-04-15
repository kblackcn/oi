/**************************************************************
    Problem: 4513
    User: qwerty123456
    Language: C++
    Result: Accepted
    Time:3024 ms
    Memory:804 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
#include<cctype>
#include<algorithm>
 
using namespace std;
 
typedef long long ll;
 
ll read() {
    ll ans = 0;
    char ch;
    while (!isdigit(ch = getchar()));
    do { ans = ans * 10 + ch - 48; } while (isdigit(ch = getchar()));
    return ans;
}
 
ll P, k;
 
ll query(ll l, ll r) {
    return (((r - l + 1) % (P << 1))*((l + r) % (P << 1)) >> 1) % P;
}
 
int calc(ll x, int px, ll y, int py) {
    if (px < py) swap(x, y), swap(px, py);
    x ^= (x &((1LL << px) - 1)); y ^= (y & ((1LL << px) - 1));
    ll t = x^y;
    ll ans = 0;
    if (k < t)(ans += query(t - k, t + (1LL << px) - 1 - k)) %= P;
    else if (k < t + (1LL << px)) (ans += query(0, t + (1LL << px) - 1 - k)) %= P;
    return ans*((1LL << py) % P) % P;
}
 
void solve() {
    ll n = read(), m = read(), ans = 0;
    k = read();
    P = read();
    ll tn = 0, tm;
    for (int i = 62; ~i; --i) {
        if (n&(1LL << i)) {
            tm = 0;
            for (int j = 62; ~j; --j)
                if (m&(1LL << j)) {
                    (ans += calc(tn, i, tm, j)) %= P;
                    tm |= (1LL << j);
                }
            tn |= 1LL << i;
        }
    }
    printf("%lld\n", ans);
}
 
int main() {
    int table[64][64];
    for (int i = 0; i < 64; ++i)
        for (int j = 0; j < 64; ++j)
            table[i][j] = i^j;
    for (int T = read(); T > 0; --T) {
        solve();
    }
}