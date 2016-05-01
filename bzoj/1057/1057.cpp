/**************************************************************
    Problem: 1057
    User: qwerty123456
    Language: C++
    Result: Accepted
    Time:2484 ms
    Memory:33588 kb
****************************************************************/
 
#include<cstdio>
#include<cmath>
#include<algorithm>
 
using namespace std;
 
const int N = 2048;
 
int a[N][N], b[N][N];
 
int s[N], sp[N], ans1, ans2;
 
int sqr(const int x) { return x*x; }
 
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            scanf("%d", a[i] + j);
    for (int j = 0; j < m; ++j)
        b[0][j] = 1;
    for (int i = 1; i < n; ++i)
        for (int j = 0; j < m; ++j)
            b[i][j] = (a[i][j] ^ a[i - 1][j]) ? b[i - 1][j] + 1 : 1;
    ans2 = 0;
    for (int i = 0; i < n; ++i) {
        int top = 0;
        for (int j = 0; j <= m; ++j) {
            bool flag = false;
            while (top > 0 && (s[top] > b[i][j] || (j > 0 && a[i][j] == a[i][j - 1]))) {
                flag = true;
                if ((j - sp[top])*s[top] > ans2) {
                    ans2 = (j - sp[top]) * s[top];
                }
                int x = min(j - sp[top], s[top]);
                if (sqr(x) > ans1) {
                    ans1 = sqr(x);
                }
                --top;
            }
            if (top > 0 && s[top] == b[i][j])continue;
            s[++top] = b[i][j];
            if (!flag || a[i][j] == a[i][j - 1])sp[top] = j;
        }
    }
    printf("%d\n%d\n", ans1, ans2);
    return 0;
}