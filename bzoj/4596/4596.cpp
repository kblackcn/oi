/**************************************************************
    Problem: 4596
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:6064 ms
    Memory:812 kb
****************************************************************/
 
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
 
#define mk(x, y) make_pair(x,y)
 
using namespace std;
 
const int N = 20;
 
const int MOD = 1e9 + 7;
 
typedef long long ll;
 
typedef pair<int, int> par;
 
typedef vector<par>::iterator iter;
 
int mt[N][N];
 
int n, m, p, q;
 
vector<par> e[N];
 
ll Gauss() {
    ll ans = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = i + 1; j < n; ++j)
            while (mt[j][i]) {
                ll t = mt[i][i] / mt[j][i];
                for (int k = i; k < n; ++k)
                    mt[i][k] = (mt[i][k] - mt[j][k] * t) % MOD;
                for (int k = i; k < n; ++k)
                    swap(mt[i][k], mt[j][k]);
                ans = -ans;
 
            }
        ans = ans*mt[i][i] % MOD;
        if (!ans)return 0;
 
    }
    return (ans + MOD) % MOD;
 
}
 
 
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n - 1; ++i) {
        scanf("%d", &m);
        while (m-- > 0) {
            scanf("%d%d", &p, &q);
            e[i].push_back(mk(p, q));
        }
    }
    ll ans = 0;
    for (int j = (1 << (n-1)) - 1; j > 0; --j) {
        memset(mt, 0, sizeof(mt));
        int c = 0;
        for (int i = 0; i < n - 1; ++i) if ((1 << i)&j) {
            ++c;
            for (iter it = e[i].begin(); it != e[i].end(); ++it) {
                int x = it->first, y = it->second;
                ++mt[x][x]; ++mt[y][y];
                --mt[x][y]; --mt[y][x];
            }
        }
        ans = (ans + Gauss()*(((n - c) & 1) ? 1 : -1) + MOD) % MOD;
    }
    printf("%lld\n", ans);
    return 0;
}