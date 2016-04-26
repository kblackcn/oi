/**************************************************************
    Problem: 4558
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:4632 ms
    Memory:824 kb
****************************************************************/
 
#include<cstdio>
#include<algorithm>
 
using namespace std;
 
typedef long long ll;
 
const int N = 2005;
const ll MOD = 1e8 + 7;
 
struct Point {
    int x, y;
    Point() {}
    Point(int _x, int _y) :x(_x), y(_y) {}
};
 
bool cmp(const Point& x, const Point& y) {
    return x.x < y.x || (x.x == y.x && x.y < y.y);
}
 
bool equals(const Point& x, const Point& y) {
    return x.x == y.x  && x.y == y.y;
}
 
int n, m, K;
 
Point ps[N];
 
ll ans = 0;
 
ll work0() {
    int k = min(n, m);
    ll ans = 0;
    for (int i = 1; i <= k; ++i) {
        ans = (ans + ((ll)n - i + 1)*((ll)m - i + 1) % MOD*i) % MOD;
    }
    return ans;
}
 
ll sum(int first, int last, int count) {
    return (((ll)count)*(first + last)) >> 1;
}
ll sum(int first, int last) {
    return sum(first, last, abs(first - last) + 1);
}
 
ll work10(int l, int r, int h) {
    int z = min(l + r, h);
    if (z == 0)return 0;
    // 2 -> x+1 -> x+1 -> l+r-z+1
    // 1 -> x -> y -> z
    ll ans = sum(2, z + 1);
    if (z > l)ans -= sum(1, z - l);
    if (z > r)ans -= sum(1, z - r);
    return ans;
}
 
 
ll work1(int x, int y) {
    int top = x, bottom = n - x, left = y, right = m - y;
    return (work10(top, bottom, left) + work10(top, bottom, right) + work10(left, right, top) + work10(left, right, bottom)
        - min(left, top) - min(top, right) - min(right, bottom) - min(bottom, left)) % MOD;
}
 
bool inrange(int x, int l, int r) {
    return l <= x && x <= r;
}
 
bool inrange(int x, int y) {
    return inrange(x, 0, n) && inrange(y, 0, m);
}
 
bool has(int x, int y) {
    static Point temp;
    temp = Point(x, y);
    return equals(*lower_bound(ps, ps + K, temp, cmp), temp);
}
 
int main() {
    scanf("%d%d%d", &n, &m, &K);
    ans = work0();
    for (int i = 0; i < K; ++i) {
        scanf("%d%d", &ps[i].x, &ps[i].y);
        ans = (ans - work1(ps[i].x, ps[i].y)) % MOD;
    }
    sort(ps, ps + K, cmp);
    int t;
    ll count2 = 0, count3 = 0, count4 = 0;
    for (int i = 0; i < K; ++i) {
        Point& p = ps[i];
        for (int j = i + 1; j < K; ++j) {
            Point& q = ps[j];
            int dx = p.x - q.x, dy = p.y - q.y;
            if (inrange(p.x + dy, p.y - dx) && inrange(q.x + dy, q.y - dx)) {
                t = 0;
                if (has(p.x + dy, p.y - dx)) ++t;
                if (has(q.x + dy, q.y - dx)) ++t;
                ++count2;
                if (t > 0) ++count3;
                if (t > 1) ++count4, ++count3;
            }
            if (inrange(p.x - dy, p.y + dx) && inrange(q.x - dy, q.y + dx)) {
                t = 0;
                if (has(p.x - dy, p.y + dx)) ++t;
                if (has(q.x - dy, q.y + dx)) ++t;
                ++count2;
                if (t > 0) ++count3;
                if (t > 1) ++count4, ++count3;
            }
            if ((abs(dx) + abs(dy)) & 1)continue;
            {
                int x = (dx - dy) >> 1, y = (dx + dy) >> 1;
                if (inrange(p.x - x, p.y - y) && inrange(q.x + x, q.y + y)) {
                    t = 0;
                    if (has(p.x - x, p.y - y)) ++t;
                    if (has(q.x + x, q.y + y)) ++t;
                    ++count2;
                    if (t > 0) ++count3;
                    if (t > 1) ++count4, ++count3;
                }
            }
        }
    }
    count3 = count3 / 3; count4 /= 6;
    ans = (ans + count2 - count3 + count4) % MOD;
    if (ans < 0)ans += MOD;
    printf("%lld\n", ans);
}