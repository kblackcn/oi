/**************************************************************
    Problem: 4511
    User: qwerty123456
    Language: C++
    Result: Accepted
    Time:48 ms
    Memory:804 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
 
int d[7];
 
int main() {
    memset(d, -1, sizeof(d));
    d[0] = 0;
    int n, s = 0, k, ans = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &k);
        s = (s + k) % 7;
        if (d[s] < 0) {
            d[s] = i;
        }
        else
            if (i - d[s]>ans) {
                ans = i - d[s];
            }
    }
    printf("%d\n", ans);
    return 0;
}