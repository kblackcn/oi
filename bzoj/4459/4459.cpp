/**************************************************************
    Problem: 4459
    User: syswow64
    Language: C++
    Result: Accepted
    Time:304 ms
    Memory:816 kb
****************************************************************/
 
#include<cstdio>
#include<cmath>
 
int main() {
    long long n;
    scanf("%lld", &n);
    long long ans = 1;
    while ((n & 1) == 0) {
        n >>= 1;
        ans += 2;
    }
    int pq = (int)sqrt(n);
    for (int p = 3; p <= pq; p += 2)
        if (n % p == 0) {
            int ct = 1;
            do {
                ct += 2;
                n /= p;
            } while (n % p == 0);
            ans *= ct;
        }
    if (n > 1)ans *= 3;
    printf("%lld\n", (ans + 1) / 2);
    return 0;
}