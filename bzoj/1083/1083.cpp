/**************************************************************
    Problem: 1083
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:32 ms
    Memory:3736 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
 
const int N = 500;
const int M = 250000;
 
struct Edge {
    int s, t, v;
 
    void read() {
        scanf("%d%d%d", &s, &t, &v);
    }
} edges[M];
 
template<int N>
struct UnionTree {
    int fa[N];
 
    void init() {
        int i = N;
        while (i-- > 0) {
            fa[i] = i;
        }
    }
 
    int findFather(int x) {
        if (fa[x] == x) return x;
        return fa[x] = findFather(fa[x]);
    }
 
    void merge(int x, int y) {
        fa[findFather(y)] = findFather(x);
    }
};
 
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; ++i) {
        edges[i].read();
    }
    UnionTree<N> data;
    int left = 0, right = 10000;
    while (left < right) {
        int middle = (left + right) >> 1;
        data.init();
        for (int i = 0; i < m; ++i) {
            if (edges[i].v <= middle) {
                data.merge(edges[i].s, edges[i].t);
            }
        }
        int x = data.findFather(1);
        for (int i = 2; i <= n; ++i) {
            if (x != data.findFather(i)) {
                x = -1;
                break;
            }
        }
        if (x < 0) {
            left = middle + 1;
        }
        else {
            right = middle;
        }
    }
    printf("%d %d\n", n - 1, left);
    return 0;
}