/**************************************************************
    Problem: 4443
    User: syswow64
    Language: C++
    Result: Accepted
    Time:360 ms
    Memory:1064 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
 
const int N = 255;
 
int a[N][N];
int n, m, k;
int maxnum;
 
void init() {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            scanf("%d", a[i] + j);
            if (a[i][j]>maxnum)maxnum = a[i][j];
        }
}
 
int b[N], c[N];
 
bool vis[N];
int par[N];
 
int limit;
 
bool fff(int p) {
    if (vis[p])return false;
    vis[p] = true;
    for (int i = 0; i < m; ++i) if(a[p][i]<=limit) {
        if (par[i] == -1) {
            par[i] = p;
            return true;
        }
        else
            if (fff(par[i])) {
                par[i] = p;
                return true;
            }
    }
    return false;
}
 
bool solve(int min) {
    memset(par, -1, sizeof(par));
    int ans = 0; limit = min;
    for (int i = 0; i < n; ++i) {
        memset(vis, 0, sizeof vis);
        if (fff(i)) {
            ++ans;
        }
    }
    return ans >= n - k + 1;
}
 
int main() {
    init();
    int left = 0, right = maxnum;
    while (left < right) {
        int middle = (left + right) >> 1;
        if (solve(middle))right = middle;
        else left = middle + 1;
    }
    printf("%d\n", left);
    return 0;
}