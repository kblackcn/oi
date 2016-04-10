/**************************************************************
    Problem: 4492
    User: qwerty123456
    Language: C++
    Result: Accepted
    Time:4504 ms
    Memory:16332 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
#include<cctype>
 
void read(int& x) {
    x = 0;
    char ch;
    while (isdigit(ch = getchar())) x = x * 10 + ch - 48;
}
 
const int N = 3e5 + 5;
const int M = 4 * N;
 
int ehead[N], next[M], tar[M];
 
int disA[N], disB[N];
 
int ct = 0;
 
int min(const int x, const int y) { return x < y ? x : y; }
 
void addEdge(const int p, const int q) {
    ++ct; next[ct] = ehead[p]; tar[ct] = q; ehead[p] = ct;
}
 
void bfs(int p, int* dis) {
    static int q[N];
    int head = -1, tail = 0;
    q[tail] = p;
    dis[p] = 0;
    do {
        p = q[++head];
        for (int x = ehead[p]; x; x = next[x]) {
            int y = tar[x];
            if (dis[y] == -1) {
                dis[y] = dis[p] + 1;
                q[++tail] = y;
            }
        }
    } while (head < tail);
}
 
int bfs2(int p) {
    static int q[N];
    static bool f[N];
    memset(f, 0, sizeof(f));
    int head = -1, tail = 0;
    q[tail] = p;
    int ans = disA[p], pp = p;
    do {
        p = q[++head];
        for (int x = ehead[p]; x; x = next[x]) {
            int y = tar[x];
            if (!f[y] && (disA[p] - disA[y] == 1) && (disB[p] - disB[y] == 1)) {
                f[y] = true;
                q[++tail] = y;
                if (disA[y] < ans) ans = disA[y];
            }
        }
    } while (head < tail);
    return disA[pp] - ans;
}
 
int main() {
    int n, m, s, d, a, b;
    read(n); read(m);
    read(s); read(d); read(a); read(b);
    for (int i = 0; i < m; ++i) {
        int p, q;
        read(p); read(q);
        addEdge(p, q);
        addEdge(q, p);
    }
    int s1, s2, d1, d2, w1, w2;
    memset(disA, -1, sizeof(disA));
    memset(disB, -1, sizeof(disB));
    bfs(a, disA); s1 = disA[s]; d1 = disA[d];
    bfs(b, disB); s2 = disB[s]; d2 = disB[d];
    w1 = d1 - s1; w2 = d2 - s2;
    if (w1 < 0 || w2 < 0) {
        puts("-1");
    }
    else if (w1 == w2) {
        int x = bfs2(s);
        int y = bfs2(d);
        printf("%d\n", x + w1 >= y ? w1 : w1 - 1);
    }
    else printf("%d\n", min(w1, w2));
    return 0;
}