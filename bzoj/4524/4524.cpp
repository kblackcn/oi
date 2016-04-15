/**************************************************************
    Problem: 4524
    User: qwerty123456
    Language: C++
    Result: Accepted
    Time:3820 ms
    Memory:124160 kb
****************************************************************/
 
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<queue>
 
typedef long long ll;
 
using namespace std;
 
int m, cnt, c[155];
bool vis[155];
ll n;
struct dat {
    ll t; int x, y, z;
};
bool operator <(dat u, dat v) { return u.t < v.t; }
priority_queue<dat> q;
int main() {
    scanf("%lld%d", &n, &m);
    ll x;
    for (int i = 2; i < 128; i++) {
        if (!vis[i]) {
            x = i;
            c[++cnt] = i;
            for (int j = 1; x <= n; j++, x *= i) q.push(dat{ x, i, j, cnt - 1 });
        }
        for (int j = i + i; j < 128; j += i) vis[j] = 1;
    }
    while (m--) {
        dat u = q.top(); q.pop();
        if (!m) printf("%lld\n", u.t);
        else if (u.y > 1)
            for (int i = 1; i <= u.z; i++) q.push(dat{ u.t / u.x*c[i], u.x, u.y - 1, i });
    }
    return 0;
}