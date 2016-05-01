/**************************************************************
    Problem: 1026
    User: shzhw
    Language: C++
    Result: Accepted
    Time:0 ms
    Memory:804 kb
****************************************************************/
 
#include<cstdio>
#include<algorithm>
 
using namespace std;
 
int d[10][11];
 
void pre() {
    for (int i = 0; i < 10; ++i)d[0][i] = 1;
    for (int i = 1; i < 10; ++i)
        for (int j = 0; j < 10; ++j) {
            d[i][j] = 0;
            for (int k = 0; k < 10; ++k)
                if (abs(j - k) > 1) {
                    d[i][j] += d[i - 1][k];
                }
            d[i][10] += d[i][j];
        }
}
 
int get(int n) {
    if (n == 0) return 0;
    if (n < 10)return n;
    int b[10], len = 0, ans = 0;
    while (n > 0) { b[len++] = n % 10; n /= 10; }
    for (int i = 0; i < len - 1; ++i) {
        for (int j = 1; j < 10; ++j)ans += d[i][j];
    }
    for (int i = 1; i < b[len - 1]; ++i) {
        ans += d[len - 1][i];
    }
    for (int i = len - 2; i > -1; --i) {
        for (int j = 0; j < b[i]; ++j) if (abs(b[i + 1] - j) > 1) {
            ans += d[i][j];
        }
        if (abs(b[i] - b[i + 1]) < 2)break;
        if (i == 0)++ans;
    }
    return ans;
}
 
int main() {
    pre();
    int l, r;
    while (scanf("%d%d", &l, &r) != EOF)
        printf("%d\n", get(r) - get(l - 1));
    return 0;
}