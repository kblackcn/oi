/**************************************************************
    Problem: 2005
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:16 ms
    Memory:1588 kb
****************************************************************/
 
#include<cstdio>
 
typedef long long ll;
 
const int N = 1e5+5;
 
ll f[N];
 
int main() {
    int n, m, k;
    scanf("%d%d", &n, &m);
    k = n>m?m:n;
    ll ans = 0;
    for(int i = k; i>0; --i) {
        f[i] = ((ll)n/i)*(m/i);
        for(int j = i+i; j<=k; j+=i)
            f[i]-=f[j];
        ans+=f[i]*(2*i-1);
    }   
    printf("%lld\n", ans);
    return 0;
}