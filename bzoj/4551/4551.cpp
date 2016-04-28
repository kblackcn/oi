/**************************************************************
    Problem: 4551
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:352 ms
    Memory:3932 kb
****************************************************************/
 
#include<cstdio>
 
const int N = 1e5+5;
const int M = N << 1;
 
int head[N], next[M], tar[M], ct;
 
void add(int x, int y) {
    next[++ct] = head[x]; tar[ct] = y; head[x] = ct;
    next[++ct] = head[y]; tar[ct] = x; head[y] = ct;
}
 
int fa[N], tg[N];
 
int main() {
    int n, q;
    scanf("%d%d", &n, &q);
    for(int i = 1; i<n; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
    }
    int l = 0, r = 1;
    static int Q[N];
    Q[0] = 1;
    while(l<r) {
        int p = Q[l++];
        for(int i = head[p]; i>0; i = next[i]) if(tar[i]!=fa[p]) {
            fa[tar[i]] = p;
            Q[r++] = tar[i];
        }
    }
    char op[4];
    tg[1] = true;
    for(int i = 0; i<q; ++i) {
        scanf("%s%d", op, &l);
        if(op[0]=='Q') {
            while(!tg[l]) l = fa[l];
            printf("%d\n", l);
        } else {
            tg[l] = true;
        }
    }
    return 0;
}