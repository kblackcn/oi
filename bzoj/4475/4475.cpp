/**************************************************************
    Problem: 4475
    User: syswow64
    Language: C++
    Result: Accepted
    Time:0 ms
    Memory:804 kb
****************************************************************/
 
#include<cstdio>
 
typedef long long ll;
 
const int P = 1e9 + 7;
 
int main()
{
    ll n, k, a = 1, b = 2;
    scanf("%lld%lld", &n, &k);
    n *= k;
    while (n > 0) {
        if (n & 1) {
            a *= b;
            a %= P;
        }
        b = (b * b) % P;
        n >>= 1;
    }
    printf("%lld\n", a);
    return 0;
}