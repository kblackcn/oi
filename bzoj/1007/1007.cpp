/**************************************************************
    Problem: 1007
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:184 ms
    Memory:2104 kb
****************************************************************/
 
#include<cstdlib>
#include<cstdio>
#include<algorithm>
 
using namespace std;
 
const long N = 50004;
 
struct Line {
    int a, b;
    int id;
} c[N];
 
double u[N];
int x[N];
 
int top = -1;
 
int cmp(const Line& x, const Line& y) {
    return x.a<y.a || (x.a==y.a && x.b>y.b);
}
 
pair<double,double> cross(const Line& a, const Line& b) {
    if(a.a==b.a) return make_pair(2147483647., 0.);
    double x = (a.b-b.b)*1.0/(b.a-a.a);
     
    return make_pair(x, x*a.a+a.b);
}
 
int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i<n; ++i) {
        scanf("%d%d", &(c[i].a), &(c[i].b));
        c[i].id = i+1;
    }
    std::sort(c, c+n, cmp);
    for(int i = 0; i<n; ++i) {
        pair<double, double> y;
        while(top>-1) {
            y = cross(c[x[top]], c[i]);
            if(u[top]<y.first) break;
            --top;
        }
        ++top;
        x[top] = i;
        if(top>0) {
            u[top] = y.first;
        } else {
            u[top] = -2147483648.;
        }
    }
    int a[N];
    for(int i = 0; i<=top; ++i) {
        a[i] = c[x[i]].id;
    }
    sort(a, a+top+1);
    for(int i = 0; i<top; ++i) {
        printf("%d ", a[i]);
    }
    printf("%d \n", a[top]);
    return 0;
}