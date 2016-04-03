/**************************************************************
    Problem: 1197
    User: syswow128
    Language: C++
    Result: Accepted
    Time:0 ms
    Memory:844 kb
****************************************************************/
 
#include<cstdio>
 
typedef long long ll;
 
ll d[21][202];
bool p[21][202];
 
void pdoi() {
    for(int i = 1; i<16; ++i) d[i][1] = 2, p[i][1] = true;
    for(int j = 1; j<101; ++j) d[1][j] = 2 * j, p[1][j] = true;
}
 
ll doi(const int x, const int y) {
    if(p[x][y]) return d[x][y];
    p[x][y] = true;
    return d[x][y] = doi(x-1, y-1) + doi(x, y-1);
}
 
int main() {
    int n, m;
    scanf("%d%d", &m, &n);
    pdoi();
    printf("%lld\n", doi(n, m));
    return 0;
}