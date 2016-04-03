/**************************************************************
    Problem: 1088
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:16 ms
    Memory:884 kb
****************************************************************/
 
#include<cstdio>
 
const long N = 10000;
 
long n, m;
 
long ans;
 
int a[N], b[N];
 
int check(){
    int i;
    for(i = 2; i<n; ++i){
        b[i] = a[i-1]-b[i-1]-b[i-2];
        if(b[i]<0||b[i]>1) return 0;
    }
    --i;
    if(b[i]+b[i-1]!=a[i]) return 0;
    return 1;
}
 
int main(){
    scanf("%ld", &n);
    for(int i = 0; i<n; ++i){
        scanf("%d", &a[i]);
    }
    if(n==1){
        puts("1");
        return 0;
    }
    if(n==2){
        if(a[0]==0) puts("1"); else
        if(a[0]==1) puts("2"); else
 
                puts("1");
        return 0;
    }
    ans = 0;
    if(a[0]==0){
        b[0] = 0; b[1] = 0;
        ans+=check();
    }
    if(a[0]==1){
        b[0] = 0; b[1] = 1;
        ans+=check();
        b[0] = 1; b[1] = 0;
        ans+=check();
    }
    if(a[0]==2){
        b[0] = 1; b[1] = 1;
        ans+=check();
    }
    printf("%ld", ans);
    return 0;
}