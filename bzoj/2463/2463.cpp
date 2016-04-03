/**************************************************************
    Problem: 2463
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:0 ms
    Memory:804 kb
****************************************************************/
 
#include<cstdio>
int n;
int main()
{
    while(scanf("%d",&n)&&n)
    {
        if(n&1)printf("Bob\n");
        else printf("Alice\n");
    }
    return 0;
}