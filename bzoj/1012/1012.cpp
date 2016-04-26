/**************************************************************
    Problem: 1012
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:456 ms
    Memory:2368 kb
****************************************************************/
 
#include<cstdio>
#include<algorithm>
 
using namespace std;
 
const int N = 200005;
 
int a[N], b[N], top, n;
 
char query[10];
 
int main() {
    int M, D, x, last = 0;
    scanf("%d%d", &M, &D);
    while (M-- > 0) {
        scanf("%s%d", query, &x);
        if (query[0] == 'A') {
            ++n;
            x = (x + last) % D;
            while (top > 0 && a[top - 1] < x) --top;
            b[top] = n;
            a[top++] = x;
        }
        else {
            x = lower_bound(b, b + top, n - x + 1) - b;
            printf("%d\n", last = a[x]);
        }
    }
    return 0;
}