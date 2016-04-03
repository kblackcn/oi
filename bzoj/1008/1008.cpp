/**************************************************************
    Problem: 1008
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:24 ms
    Memory:804 kb
****************************************************************/
 
#include<cstdio>
 
typedef long long ll;
 
const long MODX = 100003;
 
ll dfs(ll a, ll b) {
    ll res=1;
    while(b)
    {
        if(b&1) res=(res*a) % MODX;
        a=(a*a) % MODX;
        b>>=1LL;
    }
    return res;
}
 
int main() {
    ll n, m;
    scanf("%lld%lld", &m, &n);
    ll ans = dfs(m, n)-m*dfs(m-1, n-1);
    while(ans<0) ans+=MODX;
    ans = ans % MODX;
    printf("%lld\n", ans);
    return 0;
}