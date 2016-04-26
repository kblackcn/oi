/**************************************************************
    Problem: 1191
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:12 ms
    Memory:820 kb
****************************************************************/
 
#include<cstdio>
 
const int N = 1005;
 
int vis[N], par[N], frd[N][2];
 
int T;
 
bool dfs(const int p) {
    for (int i = 0; i < 2; ++i) {
        int j = frd[p][i];
        if (vis[j] == T)continue;
        vis[j] = T;
        if (par[j] == 0 || dfs(par[j])) {
            par[j] = p;
            return true;
        }
    }
    return false;
}
 
int main() {
    int n, m, ans = 0;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i) {
        T = i;
        int x, y;
        scanf("%d%d", &x, &y);
        ++x; ++y;
        frd[i][0] = x; frd[i][1] = y;
        if (dfs(i)) ++ans;
        else break;
    }
    printf("%d\n", ans);
}