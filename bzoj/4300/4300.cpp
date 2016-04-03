/**************************************************************
    Problem: 4300
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:92 ms
    Memory:1196 kb
****************************************************************/
 
#include<cstdio>
int n;
int f[100011]={};
int E[33]={};
int main()
{
    scanf("%d",&n);
    int t,m,h;
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&t);
        m=0;
        while (t!=0)
        {
              m++;
              h=t%2;t=t/2;
              if (h==1)
              {
                       if (f[E[m]]+1>f[i])
                          f[i]=f[E[m]]+1;
                       E[m]=i;
              }
        }
    }
    for (int i=1;i<=n;i++)
        if (f[i]<f[i-1]) f[i]=f[i-1];
    printf("%d",f[n]);
      
    //system("pause");
    return 0;
}
