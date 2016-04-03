/**************************************************************
    Problem: 1002
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:0 ms
    Memory:848 kb
****************************************************************/

#include<cstdio>
#include<cstring>
const int N = 102;
 
struct hd {
    int len;
    int nums[N];
};
 
hd k[N];
hd plus(hd a, int i) {
    a.nums[0]+=i;
    int x = 0;
    while(a.nums[x]>9) {
        a.nums[x+1]+=int(a.nums[x]/10);
        a.nums[x] = a.nums[x] % 10;
        ++x;
    }
    if(x>a.len) {
        a.len = x;
    }
    return a;
}
 
hd minus(hd a, const hd& b) {
    for(int i = 0; i<a.len; ++i) {
        a.nums[i]-=b.nums[i];
        if(a.nums[i]<0) {
            a.nums[i]+=10;
            --a.nums[i+1];
        }
    }
    return a;
}
hd make(int v) {
    hd ans;
    memset(ans.nums, 0, sizeof(ans.nums));
    ans.len = 1;
    return plus(ans, v);
}
hd multi(hd a, const int& v) {
    hd ans = make(0);
    int i;
    for(i = 0; (i<a.len)||(ans.nums[i]>0); ++i) {
        long x = a.nums[i] * v+ans.nums[i];
        if(x>9) {
            ans.nums[i] = x%10;
            ans.nums[i+1] = int(x/10);
        } else ans.nums[i] = x;
    }
    if(i>a.len) ans.len = i;
    else ans.len = a.len;
    return ans;
}
int main(){
    int n;
    scanf("%d", &n);
    if(n==0) {
        //printf("1");
        return 0;
    }
    k[1] = make(1);
    k[2] = make(5);
    for(int i = 3; i<=n; ++i) {
        k[i] = plus(minus(multi(k[i-1],3), k[i-2]), 2);
    }
    for(int i = k[n].len-1; i>-1; --i) {
        printf("%d", k[n].nums[i]);
    }
    return 0;
}