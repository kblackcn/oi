/**************************************************************
    Problem: 1216
    User: zxcvbnm123456
    Language: C++
    Result: Accepted
    Time:968 ms
    Memory:1200 kb
****************************************************************/
 
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<utility>
#include<queue>
#include<cstdlib>
 
typedef long long ll;
 
using namespace std;
 
namespace io {
    template<class T> void read(T&num) {
        static char CH; static bool F;
        F = false;
        for (CH = getchar(); CH<'0' || CH>'9'; F = CH == '-', CH = getchar());
        for (num = 0; CH >= '0'&&CH <= '9'; num = num * 10 + CH - '0', CH = getchar());
        F && (num = -num);
    }
 
    inline void space() { putchar(' '); }
 
    inline void ln() { putchar('\n'); }
 
    template<class T> inline void print(T p) {
        static int stk[70], tp;
        if (!p) { puts("0"); return; }
        while (p) stk[++tp] = p % 10, p /= 10;
        while (tp) putchar(stk[tp--] + '0');
    }
 
    template<class T> inline void println(T p) { print(p); ln(); }
}
 
using namespace io;
 
struct Process {
    int id, time, priority, order;
 
    bool operator <(const Process& y) const {
        return this->priority < y.priority || (this->priority == y.priority && this->order > y.order);
    }
};
 
priority_queue<Process> pq;
 
int main() {
    int now = 0, x, y, z, ct = 0;
    while (true) {
        Process p;
        if (scanf("%d", &p.id) == EOF) break;
        read(x); read(p.time); read(p.priority); p.order = ct++;
        while (!pq.empty()) {
            Process q = pq.top(); pq.pop();
            if (q.time <= x - now) {
                now += q.time;
                print(q.id); space(); println(now);
            }
            else {
                q.time -= x - now;
                pq.push(q);
                break;
            }
        }
        now = x;
        pq.push(p);
    }
    while (!pq.empty()) {
        Process q = pq.top(); pq.pop();
        now += q.time;
        print(q.id); space(); println(now);
    }
    return 0;
}