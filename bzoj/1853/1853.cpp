/**************************************************************
    Problem: 1853
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:1264 ms
    Memory:840 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 3000 + 10;
bool flag[maxn];
long long luck[maxn];
long long cnt = 0,ret = 0;
long long limit,a,b;
 
bool cmp(const long long &a,const long long &b)
{
    return a > b;
}
 
void dfs(long long num)
{
    if(num > limit)return;
    if(num != 0)luck[cnt++] = num;
    dfs(num * 10 + 6);
    dfs(num * 10 + 8);
}
 
long long gcd(long long a,long long b)
{
    long long t;
    while(b != 0)
    {
        t = a % b;
        a = b;
        b = t;
    }
    return a;
}
 
void work(int step,long long lcm,int tot)
{
    if(step == cnt)
    {
        if(tot)
        {
            long long tmp = limit / lcm;
            if(tot&1)ret += tmp;
            else ret -= tmp;
        }
        return;
    }
    for(int i = step;i < cnt;i++)
    {
        long long tmp = gcd(lcm,luck[step]);
        if((double)lcm / tmp > (double)limit / luck[step])return;
        tmp = lcm * luck[step] / tmp;
        work(i + 1,tmp,tot + 1);
    }
}
 
long long calc(long long x)
{
    if(x < 6)return 0;
    ret = 0,cnt = 0;
    limit = x;
    dfs(0);
    stable_sort(luck,luck + cnt);
    for(int i = 0;i < cnt;i++)
    {
        flag[i] = true;
        for(int j = 0;j < i;j++)
        {
            if(luck[i] % luck[j] == 0)flag[i] = false;
        }
    }
    int tmp = cnt;
    cnt = 0;
    for(int i = 0;i < tmp;i++)
    {
        if(flag[i])luck[cnt++] = luck[i];
    }
    stable_sort(luck,luck + cnt,cmp);
    for(int i = 0;i < cnt;i++)
    {
        work(i,1,0);
    }
    return ret;
}
 
int main()
{
 
    scanf("%lld%lld",&a,&b);
    long long ans = calc(b) - calc(a - 1);
    printf("%lld",ans);
    return 0;
}