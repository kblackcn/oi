/**************************************************************
    Problem: 3504
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:12 ms
    Memory:980 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
#include<algorithm>
 
using namespace std;
 
const int N = 60;
const int M = N*N * 4;
const int inf = 1000;
 
int head[N], ct;
 
struct Edge {
    int tar, w, next;
    Edge() {}
    Edge(int x, int y, int z) :tar(x), w(y), next(z) {}
} e[M];
 
void clear() {
    ct = 0;
    memset(head, 255, sizeof(head));
}
 
int insert(int s, int t, int ws, int wt) {
    e[ct] = Edge(t, ws, head[s]); head[s] = ct++;
    e[ct] = Edge(s, wt, head[t]); head[t] = ct++;
    return ct - 2;
}
 
char line[N];
 
int S, T;
 
int q[N], h[N];
bool vis[N];
 
bool bfs() {
    memset(h, 127, sizeof(h));
    int hd = -1, tl = 0;
    q[tl] = S;
    h[S] = 0;
    while (hd < tl) {
        int p = q[++hd];
        for (int i = head[p]; i > -1; i = e[i].next) if (e[i].w > 0) {
            int j = e[i].tar;
            if (h[p] + 1 < h[j]) {
                h[j] = h[p] + 1;
                q[++tl] = j;
            }
        }
    }
    return h[T] < N;
}
 
int dfs(const int p, int flow) {
    if (p == T) {
        return flow;
    }
    int ans = 0;
    for (int i = head[p]; i > -1; i = e[i].next)
        if (e[i].w > 0 && h[e[i].tar] == h[p] + 1) {
            int j = e[i].tar;
            int t = dfs(j, min(flow, e[i].w));
            flow -= t; e[i].w -= t; e[i ^ 1].w += t; ans += t;
        }
    return ans;
}
 
int dinic() {
    int ans = 0;
    while (bfs())ans += dfs(S, inf);
    return ans;
}
 
void rl(int x) {
    head[x] = e[head[x]].next;
}
 
int main() {
    int n, a1, a2, an, b1, b2, bn;
    while (scanf("%d%d%d%d%d%d%d", &n, &a1, &a2, &an, &b1, &b2, &bn) != EOF) {
        clear();
        for (int i = 0; i < n; ++i) {
            scanf("%s", line);
            for (int j = i + 1; j < n; ++j)
                if (line[j] == 'O') {
                    insert(i, j, 1, 1);
                }
                else if (line[j] == 'N') {
                    insert(i, j, inf, inf);
                }
        }
        int maxct = ct;
        S = n, T = n + 1;
        insert(S, a1, an, 0);
        insert(S, b1, bn, 0);
        insert(a2, T, an, 0);
        insert(b2, T, bn, 0);
        if (dinic() != an + bn) {
            puts("No");
            continue;
        }
        for (int i = 0; i < maxct; i += 2) {
            e[i].w = e[i + 1].w = (e[i].w + e[i + 1].w) >> 1;
        }
        rl(S); rl(a1); rl(S); rl(b1);
        rl(T); rl(a2); rl(T); rl(b2);
        insert(S, a1, an, 0);
        insert(S, b2, bn, 0);
        insert(a2, T, an, 0);
        insert(b1, T, bn, 0);
        if (dinic() != an + bn) {
            puts("No");
            continue;
        }
        else {
            puts("Yes");
            continue;
        }
    }
    return 0;
}