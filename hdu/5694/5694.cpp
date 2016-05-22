#include<iostream>

using namespace std;

typedef long long ll;

ll count(ll x, int mx) {
    if (x == 0)return 0;
    if (x == 1)return 1;
    for (ll i = (1LL << mx); i > 1; i = i >> 1, --mx) if (x >= i) {
        x -= i;
        return (i >> 1) + 1 + x - ((i >> 1) - count(i - 1 - x, mx));
    }
}

int main() {
    int T;
    cin >> T;
    while (T-- > 0) {
        ll x, y;
        cin >> x >> y;
        cout << count(y, 60) - count(x - 1, 60) << endl;
    }
}