/**************************************************************
    Problem: 1816
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:0 ms
    Memory:804 kb
****************************************************************/
 
#include<cstdio>
#include<cmath>
#include<cstdlib>
 
typedef long long ll;
 
const long N = 55;
 
ll a[N];
 
ll min(ll a, ll b){
    return a>b?b:a;
}
 
long n, m;
 
bool judge(long x){
    int t = min(m,x);
    for(int i = 0; i<n; ++i){
        if(a[i]<x){
            t-=(x-a[i]);
            if(t<0) return false;
        }
    }
    return true;
}
 
int main(){
    scanf("%ld%ld", &n, &m);
    for(int i = 0; i<n; ++i){
        scanf("%ld", &a[i]);
    }
    long left, right, mid, ans;
    left = 0; right = 1000000000;
    while(left<=right){
        mid = (left+right) >> 1;
        if(judge(mid)){
            ans = mid;
            left = mid+1;
        }else{
            right = mid-1;
        }
    }
    printf("%ld", ans);
    return 0;
}