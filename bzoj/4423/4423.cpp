/**************************************************************
    Problem: 4423
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:1492 ms
    Memory:18500 kb
****************************************************************/
 
#include<cstdio>
 
const int N = 1.5e3 + 5;
const int M = N*N;
 
int fa[M], n, k;
 
int id[N][N];
 
char op[2], ox[2];
 
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
 
int main() {
    scanf("%d%d", &n, &k);
    bool ans = true;
    int cnt = 0;
    for (int i = 1; i < n; ++i)
        for (int j = 1; j < n; ++j)
            ++cnt, id[i][j] = fa[cnt] = cnt;
    while (k-- > 0) {
        int x, y, fx, fy;
        if (ans) {
            scanf("%d%d%s", &x, &y, op);
            scanf("%d%d%s", &fx, &fy, ox);
        }
        else {
            scanf("%d%d%s", &fx, &fy, ox);
            scanf("%d%d%s", &x, &y, op);
        }
        fx = find(id[x][y]);
        fy = find(op[0] == 'N' ? id[x - 1][y] : id[x][y - 1]);
        if (ans = (fx != fy))fa[fx] = fy;
        puts(ans ? "TAK" : "NIE");
    }
    return 0;
}