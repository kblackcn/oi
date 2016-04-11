/**************************************************************
    Problem: 4525
    User: qwerty123456
    Language: C++
    Result: Accepted
    Time:60 ms
    Memory:1000 kb
****************************************************************/
 
#include<cstdio>
#include<algorithm>
 
const int N = 5e4 + 5;
 
int a[N];
int n, k;
 
bool test(const int P) {
    int ans = 1, x = a[0];
    int p = (P << 1);
    for (int i = 1; i < n; ++i) {
        if (a[i] > x + p) {
            x = a[i];
            ++ans;
        }
    }
    return ans <= k;
}
 
int main() {
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; ++i) {
        scanf("%d", a + i);
    }
    std::sort(a, a + n);
    int l = 1, r = a[n-1];
    while (l < r) {
        int mid = (l + r) >> 1;
        if (test(mid)) r = mid; else l = mid + 1;
    }
    printf("%d\n", l);
    return 0;
}