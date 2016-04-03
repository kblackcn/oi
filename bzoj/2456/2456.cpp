/**************************************************************
    Problem: 2456
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:392 ms
    Memory:804 kb
****************************************************************/
 
#include<cstdio>
 
int main(){
    long n, d, m = 0, now;
    scanf("%ld", &n);
    while(n-->0) {
        scanf("%ld", &d);
        if(now==d) ++m;
        else {
            if(--m<=0) {
                m = 1;
                now = d;
            }
        }   
    }
    printf("%ld", now);
    return 0;
}