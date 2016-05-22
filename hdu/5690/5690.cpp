#include<cstdio>
#include<iostream>
#include<cstring>

using namespace std;

const int N = 1e4 + 5;

typedef long long ll;

int num[N];
int exist[N];

void put(bool flag) {
    puts(flag ? "Yes" : "No");
}

int main() {
    int T;
    scanf("%d", &T);
    for (int TT = 1; TT <= T; ++TT) {
        printf("Case #%d:\n", TT);
        int x, k, c;
        ll m;
        cin >> x >> m >> k >> c;
        memset(exist, 255, sizeof(exist));
        bool flag = false;
        int i;
        num[0] = 0;
        exist[0] = 0;
        for (i = 1; i <= m; ++i) {
            num[i] = (num[i - 1] * 10 + x) % k;
            if (exist[num[i]] >= 0) {
                flag = true; break;
            }
            exist[num[i]] = i;
        }
        if (i == m) {
            put(num[i] == c);
        }
        else {
            int head = exist[num[i]];
            int size = i - head;
            m = (m - head) % size + head;
            put(num[m] == c);
        }
    }
    return 0;
}