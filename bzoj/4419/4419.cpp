/**************************************************************
    Problem: 4419
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:2112 ms
    Memory:16432 kb
****************************************************************/
 
#include<cstdio>
#include<set>
 
using namespace std;
 
const int N = 200005;
 
int got[N], push[N];
 
int n, m;
 
set<int> r[N];
 
int main() {
    scanf("%d%d", &n, &m);
    while (m-- > 0) {
        char op;
        scanf("\n%c", &op);
        int p, q;
        switch (op) {
        case '!':
            scanf("%d", &p);
            ++push[p];
            break;
        case '+':
            scanf("%d %d", &p, &q);
            got[p] -= push[q]; r[p].insert(q);
            got[q] -= push[p]; r[q].insert(p);
            break;
        case '-':
            scanf("%d %d", &p, &q);
            got[p] += push[q]; r[p].erase(q);
            got[q] += push[p]; r[q].erase(p);
            break;
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (set<int>::iterator it = r[i].begin(); it != r[i].end(); ++it) {
            got[i] += push[*it];
        }
    }
    printf("%d", got[1]);
    for (int i = 2; i <= n; ++i) {
        printf(" %d", got[i]);
    }
    printf("\n");
    return 0;
}