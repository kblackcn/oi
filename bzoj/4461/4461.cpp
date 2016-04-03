/**************************************************************
    Problem: 4461
    User: syswow64
    Language: C++
    Result: Accepted
    Time:156 ms
    Memory:804 kb
****************************************************************/
 
#include<cstdio>
#include<cstdlib>
#include<cstring>
 
int m, P;
 
struct matrix {
    int dat[32][32];
};
 
bool single[400];
int len;
 
void init() {
    char ch;
    int pos = 0;
    int num[1024];
    memset(num, 0, sizeof(num));
    while ((ch = getchar()) != ' ') {
        num[pos++] = ch - 48;
    }
    for (int x = 0, y = pos - 1; x < y; ++x, --y) {
        int t = num[x];
        num[x] = num[y];
        num[y] = t;
    }
    len = 0;
    while (true) {
        for (int i = pos - 1; i >= len; --i) {
            num[i] *= 5;
            num[i + 1] += num[i] / 10;
            num[i] %= 10;
        }
        single[len] = num[len] == 5;
        ++len;
        if (num[pos] > 0)++pos;
        if (pos <= len + 1 && num[len] == 0)break;
    }
    int x = 0;
    while (!single[x]) {
        single[x] = true;
        ++x;
    }
    single[x] = false;
    if (x + 1 == len)--len;
    scanf("%d%d", &m, &P);
}
 
int mask;
 
void multi(const matrix x, const matrix y, matrix& z) {
    memset(z.dat, 0, sizeof(z.dat));
    for (int i = 0; i <= mask; ++i)
        for (int j = 0; j <= mask; ++j)
            for (int k = 0; k <= mask; ++k) {
                z.dat[i][j] += x.dat[i][k] * y.dat[k][j];
            }
    for (int i = 0; i <= mask; ++i)
        for (int j = 0; j <= mask; ++j) {
            z.dat[i][j] %= P;
        }
}
 
void solve() {
    matrix dis, kit;
    memset(kit.dat, 0, sizeof(kit.dat));
    memset(dis.dat, 0, sizeof(dis.dat));
    mask = (1 << m) - 1;
    for (int i = 0; i <= mask; ++i)
        for (int j = 0; j <= mask; ++j) {
            int k = i & j;
            kit.dat[i][j] = (k & (k >> 1)) == 0;
            k = (i^mask) & (j^mask);
            kit.dat[i][j] &= (k & (k >> 1)) == 0;
        }
    for (int i = 0; i <= mask; ++i) {
        dis.dat[0][i] = 1;
    }
    for (int i = 0; i < len; ++i) {
        if (single[i])
            multi(dis, kit, dis);
        multi(kit, kit, kit);
    }
    int ans = 0;
    for (int i = 0; i <= mask; ++i)
        for (int j = 0; j <= mask; ++j) {
            ans += dis.dat[i][j];
        }
    printf("%d", ans %P);
}
 
int main() {
    init();
    solve();
    return 0;
}