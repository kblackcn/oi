/**************************************************************
    Problem: 2440
    User: qwerty123456
    Language: C++
    Result: Accepted
    Time:1004 ms
    Memory:1260 kb
****************************************************************/
 
#include<cstdio>
#include<cctype>
#include<cmath>
#include<map>
 
typedef long long ll;
 
int read() {
    int ans = 0;
    char ch;
    while (!isdigit(ch = getchar()));
    do {
        ans = ans*10 + ch - 48;
    } while (isdigit(ch = getchar()));
    return ans;
}
 
const int N = 5e4 + 5;
 
int ct;
 
int prime[N], mu[N];
bool mark[N];
 
std::map<int, ll> cache;
 
ll get(int x) {
    std::map<int, ll>::iterator it = cache.find(x);
    if (it != cache.end()) {
        return it->second;
    }
    ll sum = 0;
    int t = sqrt(x);
    for (int i = 1; i <= t; i++)
        sum += x / (i*i)*mu[i];
    return cache[x] = sum;
}
 
int main() {
    mu[1] = 1;
    for (int i = 2; i < N; ++i) {
        if (!mark[i]) {
            prime[ct++] = i;
            mu[i] = -1;
        }
        for (int j = 0; j < ct && i*prime[j] < N; ++j) {
            mark[i*prime[j]] = true;
            if (i%prime[j] == 0) { mu[i*prime[j]] = 0; break; }
            else mu[i*prime[j]] = -mu[i];
        }
    }
 
    for (int T = read(); T > 0; --T) {
        int k = read();
        ll ans;
        ll l = k, r = 1644934081;
        while (l <= r)
        {
            ll mid = (l + r) >> 1;
            if (get(mid) >= k)ans = mid, r = mid - 1;
            else l = mid + 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}