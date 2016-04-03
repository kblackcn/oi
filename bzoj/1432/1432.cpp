/**************************************************************
    Problem: 1432
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:0 ms
    Memory:804 kb
****************************************************************/
 
#include<cstdio>
 
int main(){
    int n,k;
    scanf("%d%d", &n, &k);
    if (n-k+1<k)k=n-k+1;
    if (n==1) puts("1"); 
    else printf("%d", 2*k);
    return 0;
}