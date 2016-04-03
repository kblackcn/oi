/**************************************************************
    Problem: 1192
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:0 ms
    Memory:804 kb
****************************************************************/
 
#include<cstdio>
 
int main(){
    int n, ans(0);
    scanf("%d", &n);
    while(n>0){
        ++ans;
        n >>= 1;
    }
    printf("%d", ans);
    return 0;
}