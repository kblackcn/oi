/**************************************************************
    Problem: 1800
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:0 ms
    Memory:804 kb
****************************************************************/
 
#include<cstdio>
#include<cstdlib>
 
int main() {
    int n, a[20], count;
    scanf("%d%d", &n, a);
    for(int i = 1; i<n; ++i) {
        scanf("%d", a+i);
        a[i] += a[i-1];
    }
    for(int i = 0; i<n; ++i) {
        for(int j = i+1; j<n; ++j) {
            for(int x = j+1; x<n; ++x) {
                for(int y = x+1; y<n; ++y) {
                    if(a[j]-a[i]==a[y]-a[x] &&  (2*a[x]-2*a[i]==a[n-1])) {
                        ++count;
                    }
                }
            }
        }
    }
    printf("%d\n", count);
    return 0;
}