#include<set>
#include<map>
#include<ctime>
#include<queue>
#include<cmath>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define ll long long
#define inf 1000000000 
using namespace std;
int read()
{
    int x = 0, f = 1; char ch = getchar();
    while (ch<'0' || ch>'9') { if (ch == '-')f = -1; ch = getchar(); }
    while (ch >= '0'&&ch <= '9') { x = x * 10 + ch - '0'; ch = getchar(); }
    return x*f;
}
int T, n, m, cnt, top;
int last[100005], d[100005], ans[100005];

priority_queue<int, vector<int> >q;
struct edge {
    int to, next;
    edge() {}
    edge(int x, int y) :to(x), next(y) {}
}e[100005];
void insert(int u, int v)
{
    e[++cnt] = edge(v, last[u]); last[u] = cnt;
}
void solve(int x)
{
    q.pop(); ans[++top] = x;
    for (int i = last[x]; i; i = e[i].next)
    {
        d[e[i].to]--;
        if (d[e[i].to] == 0)q.push(e[i].to);
    }
}

int main() {
    int T = read();
    for (int TT = 1; TT <= T; ++TT) {
        //printf("Case #%d:\n", TT);
        cnt = top = 0;
        memset(last, 0, sizeof(last));
        memset(d, 0, sizeof(d));
        n = read(); m = read();
        for (int i = 1; i <= m; i++)
        {
            int v = read(), u = read();
            insert(v, u); d[u]++;
        }
        for (int i = 1; i <= n; i++)if (!d[i])q.push(i);
        while (!q.empty())
            solve(q.top());
        int min = n;
        long long result = 0;
        for (int i = 1; i <= n; ++i) {
            if (ans[i] < min)min = ans[i];
            result += min;
        }
        cout << result << endl;
    }
    return 0;
}