/**************************************************************
    Problem: 1607
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:884 ms
    Memory:9476 kb
****************************************************************/
 
#include<iostream>
#include<cstdio>
#include<cstring>
#define inf 0x7fffffff
using namespace std;
inline int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int n,mx;
int a[100005],cnt[1000005],s[1000005];
int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        a[i]=read();
        cnt[a[i]]++;
        mx=max(a[i],mx);
    }
    for(int i=1;i<=mx;i++)
        if(cnt[i])
        for(int j=i;j<=mx;j+=i)
            s[j]+=cnt[i];
    for(int i=1;i<=n;i++)
        printf("%d\n",s[a[i]]-1); 
    return 0;
}