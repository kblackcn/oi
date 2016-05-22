#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cctype>

using namespace std;

#define black(x, v) memset((x), v, sizeof(x))

namespace rw {
    void read(int& out) {
        char ch; while (!isdigit(ch = getchar()));
        out = ch - 48; while (isdigit(ch = getchar())) out += (out << 3) + out + ch - 48;
    }

    void read(long long& out) {
        char ch; while (!isdigit(ch = getchar()));
        out = ch - 48; while (isdigit(ch = getchar())) out += (out << 3) + out + ch - 48;
    }

    class writeSession {
        static const int FIRST_TIME = 0;
        static const int NORMAL = 1;

        int state;

        char nextToken() {
            if (state == FIRST_TIME) {
                state = NORMAL;
                return '\0';
            }
            else return ' ';
        }
    public:

        writeSession() {
            this->state = FIRST_TIME;
        }

        void put(const int& v) {
            printf("%d%c", v, this->nextToken());
        }

        void put(const long long& v) {
            printf("%lld%c", v, this->nextToken());
        }

        void put(const double& v) {
            printf("%lf%c", v, this->nextToken());
        }

        void put(const long double& v) {
            printf("%llf%c", v, this->nextToken());
        }

        void end() {
            printf("\n");
            state = FIRST_TIME;
        }
    };

    writeSession session;
}

namespace mtc {

    typedef void(*initFunction)();

    typedef void(*solveFunction)(int number);

    template<initFunction init, solveFunction solve>
    void multi() {
        int T;
        rw::read(T);
        for (int count = 0; count<T; ++count) {
            init();
            solve(count);
        }
    }
}

using namespace rw;

using namespace mtc;

const int MOD = 1000000007;

char st[1005];

long long cache[505];

void init() {
    scanf("%s", st);
}

long long extgcd(long long a, long long b, long long & x, long long & y)
{
    if (b == 0) { x = 1; y = 0; return a; }
    long long d = extgcd(b, a % b, x, y);
    long long t = x; x = y; y = t - a / b * y;
    return d;
}

void ModIt(long long & ans) {
    if(ans<0) {
        ans+=((-ans)/MOD+1)*MOD;
    }
    ans %= MOD;
}

long long di(long long a, long long b) {
    long long x, y;
    long long d = extgcd(b, MOD, x, y);
    while (b*x+MOD*y!=d)
     ;
    
    ModIt(x);
    return (a*x) % MOD;
}

void solve(int ___) {
    int ct[27];
    black(ct, 0);
    int len = strlen(st);
    for (int i = 0; i<len; ++i) {
        ++ct[st[i] - 'a'];
    }
    int warning = 0;
    for (int i = 0; i<26; ++i) {
        if (ct[i] & 1) {
            if (warning>0) {
                //session.put(0);
                //session.end();
                printf("0\n");
                return;
            }
            ++warning;
        }
        ct[i] >>= 1;
    }
    len >>= 1;
    long long ans = cache[len];
    for (int i = 0; i < 26; ++i) {
        ans = di(ans, cache[ct[i]]);
        ModIt(ans);
    }
    printf("%lld\n",ans);
    //session.put(ans);
    //session.end();
}

int main() {
    cache[0] = 1;
    for (int i = 1; i < 501; ++i) {
        cache[i] = (cache[i - 1] * i) % MOD;
    }
    multi<init, solve>();
    return 0;
}