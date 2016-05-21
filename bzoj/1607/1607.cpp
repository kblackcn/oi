/**************************************************************
    Problem: 1607
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:976 ms
    Memory:9008 kb
****************************************************************/
 
#include<cstdio>
 
const int N = 1e5 + 5;
const int M = 1e6 + 5;
 
int a[N], mx;
int cnt[M], ans[M];
 
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
        ++cnt[a[i]];
        if (a[i] > mx)mx = a[i];
    }
    for (int i = 1; i <= mx; ++i)
        if (cnt[i])
            for (int j = i; j <= mx; j += i)
                ans[j] += cnt[i];
    for (int i = 0; i < n; ++i)
        printf("%d\n", ans[a[i]] - 1);
    return 0;
}