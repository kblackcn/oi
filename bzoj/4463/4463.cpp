/**************************************************************
    Problem: 4463
    User: syswow64
    Language: C++
    Result: Accepted
    Time:128 ms
    Memory:808 kb
****************************************************************/
 
#include<cstdio>
#include<cstdlib>
#include<cstring>
 
const int P = 1000003;
const int maxSiz = 29;
int siz = 29;
 
struct matrix {
    long long dat[maxSiz][maxSiz];
public:
 
    matrix() {
        this->clear();
    }
 
    matrix(const matrix& another) {
        this->clone(another);
    }
 
    matrix& operator *=(const matrix& another) {
        matrix z;
        for (int i = 0; i < siz; ++i)
            for (int j = 0; j < siz; ++j) {
                for (int k = 0; k < siz; ++k) {
                    z.dat[i][j] += this->dat[i][k] * another.dat[k][j];
                }
            }
        for (int i = 0; i < siz; ++i)
            for (int j = 0; j < siz; ++j) {
                this->dat[i][j] = z.dat[i][j] % P;
            }
        return *this;
    }
 
    matrix& operator +=(const matrix& another) {
        for (int i = 0; i < siz; ++i)
            for (int j = 0; j < siz; ++j) {
                this->dat[i][j] = (this->dat[i][j] + another.dat[i][j]) % P;
            }
        return *this;
    }
 
    void clone(const matrix& another) {
        memcpy((void*)another.dat, this->dat, sizeof(this->dat));
    }
 
    void clear() {
        memset(this->dat, 0, sizeof(this->dat));
    }
};
 
long long n;
 
void init() {
    scanf("%lld", &n);
}
 
void solve() {
    matrix dis, kit;
    dis.dat[0][2] = 1;
    for (int i = 1; i <= 9; ++i) {
        int j = (i - 1) * 3;
        kit.dat[j][0] = 100;
        kit.dat[j + 1][0] = i * 20;
        kit.dat[j + 2][0] = i*i;
        kit.dat[j + 1][1] = 10;
        kit.dat[j + 2][1] = i;
        kit.dat[j + 2][2] = 1;
    }
    kit.dat[0][27] = 1; kit.dat[27][27] = 1;
    kit.dat[1][28] = 1; kit.dat[28][28] = 1;
    for (int i = 0; i < 24; ++i) {
        kit.dat[i][i + 3] = 1;
    }
    while (n > 0) {
        if (n & 1) {
            dis *= kit;
        }
        kit *= kit;
        n >>= 1;
    }
    long long sum2 = dis.dat[0][0] + dis.dat[0][27];
    long long sum = dis.dat[0][1] + dis.dat[0][28];
    long long ans = sum*sum - sum2;
    if (ans < 0)ans += ((-ans) / P + 1)*P;
    ans %= P;
    if (ans & 1 == 1)ans += P;
    ans /= 2;
    printf("%lld\n", ans);
}
 
int main() {
    init();
    solve();
    return 0;
}