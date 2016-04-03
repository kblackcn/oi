/**************************************************************
    Problem: 4421
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:64 ms
    Memory:804 kb
****************************************************************/
 
#include<cstdio>
 
const int MOD = 1e9 + 7;
 
int main() {
    int n, m;
    scanf("%d%d\n", &n, &m);
 
    long long ans = 0;
     
    int x = 0;
 
    for (int i = 0; i < n; ++i) {
        x = x * 10 + getchar() - 48;
        x %= m;
        if (x == 0) {
            ans = ans == 0 ? 1 : (ans << 1) % MOD;
        }
    }
 
    printf("%d\n", x == 0 ? ans : 0);
    return 0;
}
