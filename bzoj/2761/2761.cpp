/**************************************************************
    Problem: 2761
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:916 ms
    Memory:1072 kb
****************************************************************/
 
#include<cstdio>
#include<set>
 
using namespace std;
 
int main(){
    long x;
    scanf("%ld", &x);
    while(x-->0){
        set<long> st;
        long n;
        bool first = true;
        scanf("%ld", &n);
        while(n-->0){
            long p;
            scanf("%ld", &p);
            if(st.find(p)==st.end()){
                st.insert(p);
                if(first){
                    first = false;
                    printf("%ld", p);
                }
                else    printf(" %ld", p);
            }
        }
        printf("\n");
    }
}