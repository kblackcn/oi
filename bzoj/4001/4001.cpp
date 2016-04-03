/**************************************************************
    Problem: 4001
    User: gzlmr
    Language: C++
    Result: Accepted
    Time:0 ms
    Memory:1272 kb
****************************************************************/
 
#include<cstdio>
#include<iostream>
#include<ios>
 
using namespace std;
 
typedef long long ll;
 
const long N = 1000;
 
int main() {
    cout.setf(ios::fixed);
    cout.precision(9);  
    ll n;
    cin >> n;
    cout<<(n*(n+1)*1.0)/(2*(2*n-1))<<endl;
    return 0;
}