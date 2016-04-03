/**************************************************************
    Problem: 1968
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:244 ms
    Memory:54008 kb
****************************************************************/
 
#include<cstdio>
#include<iostream>
 
typedef long long ll;
 
const long N = 10000007;
using namespace std;
 
long prime[1000000],ans[N],cnt;
bool vis[N];
 
int main() {
    long n;
    scanf("%ld", &n);
    cnt=0;
    ans[0] = 0;
    ans[1] = 1;
    int x;  
    for(int i=2;i<=n;i++)  
    {  
        if(!vis[i])  
        {  
            prime[++cnt]=i;
            ans[i] = 2;
        }  
        for(int k=1;k<=cnt&&prime[k]*i<=n;++k)  
        {  
            x=prime[k]*i;  
            vis[x]=true;
            if(i%prime[k]!=0) {
                ans[x] = ans[i]*2;
            } else {
                ans[x] = ans[i]*2-ans[i/prime[k]];
            }
        }  
    }  
    ll s = 0;
    for(long i = 0; i<=n; ++i){
        s+=ans[i];
    }
    cout << s << endl;
    return 0;
}