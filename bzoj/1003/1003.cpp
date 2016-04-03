/**************************************************************
    Problem: 1003
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:28 ms
    Memory:1808 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
 
const long N = 22;
 
const long M = 105;
 
long n, m, k;
 
long a[N][N];
long b[N][M];
 
long d[M][M][N];
long u[M][M];
 
long w[N*N], iq[N];
 
bool ava[N];
 
long token;
 
void spfa(const long p, const long q){
    ++token;
    long head = -1, tail = 0;
    long* c = d[p][q];
    w[0] = 0;
    iq[0] = token;
    c[0] = 1;
    for(int i = 0; i<n; ++i)
        ava[i] = (b[i][p]==b[i][q])&&((b[i][q]&1)==0);
    while(head<tail){
        long v = w[++head];
        for(int i = 0; i<n; ++i)
            if(ava[i]){
                long x = a[v][i];
                if(x==0) continue;
                if(c[i]==0||c[i]>c[v]+x){
                    c[i] = c[v]+x;
                    if(iq[i]!=token){
                        iq[i] = token;
                        w[++tail] = i;
                    }
                }
            }
        iq[v] = 0;  
    }
    u[p][q] = c[n-1]-1; 
}
 
int main(){
    long vx;
    scanf("%ld%ld%ld%ld", &m, &n, &k, &vx);
    while(vx-->0) {
        long p, q, r;
        scanf("%ld%ld%ld", &p, &q, &r);
        a[q-1][p-1] = r;
        a[p-1][q-1] = r;
    }
    scanf("%ld", &vx);
    while(vx-->0) {
        long p, q, r;
        scanf("%ld%ld%ld", &p, &q, &r);
        ++b[p-1][q];
        ++b[p-1][r+1];
    }
    for(int i = 0; i<n; ++i)
        for(int j = 1; j<=m; ++j)
            b[i][j] += b[i][j-1];
    for(int i = 1; i<=m; ++i)
        for(int j = i; j<=m; ++j)
            spfa(i,j);
    long ans[M];
    memset(ans, 127, sizeof(ans));
    ans[0] = 0;
    for(int i = 1; i<=m; ++i)
        for(int j = i; j>0; --j){
            if(u[j][i]<1) continue;
            long v = ans[j-1]+u[j][i]*(i+1-j)+k;
            if(v<ans[i]){
                ans[i] = v;
            }
        }
    printf("%ld\n", ans[m]-k);
    return 0;
}