#include<cstdio>
#include<iostream>

typedef long long ll;

const int N = 1e5 + 5;
const int MOD = 1000000007;

ll C[N];

ll extgcd(ll a, ll b, ll & x, ll & y)
{
    if (b == 0) { x = 1; y = 0; return a; }
    ll d = extgcd(b, a % b, x, y);
    ll t = x; x = y; y = t - a / b * y;
    return d;
}

ll di(ll x, ll y) {
    ll a, b;
    extgcd(y, MOD, a, b);
    return (x*a) % MOD;
}

ll calc(int n, int m) {
    return di(C[n], (C[n - m] * C[m]) % MOD);
}

int main() {
    C[0] = 1;
    for (int i = 1; i < N; ++i) {
        C[i] = C[i - 1] * i % MOD;
    }
    int n, m;
    while (scanf("%d%d", &n, &m) != EOF) {
        n -= 2; m -= 2;
        ll ans = 0;
        for (int i = 0; i <= n && i <= m; ++i) {
            ans += calc(n, i)*calc(m, i);
            ans %= MOD;
        }
        ans += MOD;
        ans %= MOD;
        std::cout << ans << std::endl;
    }
}