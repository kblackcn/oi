#include<cstdio>
#include<cstring>

const int N = 8e3 + 5;

int n;
int a[N];

int bs[N * 2];

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 0; i < n; ++i)scanf("%d", a + i);
        for (int i = 0; i < n; ++i) {
            memset(bs, 0, sizeof(bs));
            int* b = bs + n;
            int v;
            v = 0;
            b[0] = 1;
            for (int j = i - 1; j > -1; --j)
                v += a[j] < a[i] ? 1 : -1,
                ++b[v];
            v = 0;
            int ans = b[0];
            for (int j = i + 1; j < n; ++j) {
                v += a[j] < a[i] ? -1 : 1;
                ans += b[v];
            }
            printf("%d%c", ans, i == n - 1 ? '\n' : ' ');
        }
    }
}