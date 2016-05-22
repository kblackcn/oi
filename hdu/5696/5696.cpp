#include<cstdio>

typedef long long ll;

const int N = 1e6 + 5;

int n;
int a[N];
ll ans[N];
int lb[N], rb[N];

int s[N], top;

void update(int& x, const int y) {
    if (y > x) x = y;
}

void update(ll& x, const ll y) {
    if (y > x) x = y;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) scanf("%d", a + i), ans[i] = 0;
        a[0] = a[n + 1] = (-1e9 - 1);
        top = 0;
        s[top] = 0;
        for (int i = 1; i <= n + 1; ++i) {
            while (top > 0 && a[i] < a[s[top]]) rb[s[top--]] = i;
            lb[i] = s[top];
            s[++top] = i;
        }
        lb[0] = 0; rb[n + 1] = n + 1;
        for (int i = 1; i <= n; ++i) {
            int l = i, r = i;
            ll min = a[i];
            while (l > 0 && r <= n) {
                int len = rb[r] - lb[l] - 1;
                update(ans[len], a[i] * min);
                if (a[lb[l]] < a[rb[r]]) {
                    r = rb[r];
                    min = a[r];
                }
                else {
                    l = lb[l];
                    min = a[l];
                }
            }
        }
        for (int i = n - 1; i > 0; --i) update(ans[i], ans[i + 1]);
        for (int i = 1; i <= n; ++i) printf("%lld\n", ans[i]);
    }
    return 0;
}