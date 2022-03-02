#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <cstdio>
#include <string>
#include <cmath>
#include <queue>
#include <tuple>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <random>
#include <set>
#include <stack>
#include <time.h>
#include <unordered_map>
#include <unordered_set>

//#include <bits/stdc++.h>
#define maxs(x,y) x = max(x,y)
#define mins(x,y) x = min(x,y)
#define rep(i,n) for(int (i)=0;(i)<(n);(i)++)
#define repr(i, n) for (int i = (n) - 1; i >= 0; i--)
#define FOR(i,i0,n) for(int (i)=(i0);(i)<(n);(i)++)
#define FORR(i,i0,n) for(int (i)=(n)-1; (i)>=(i0);(i)--)
#define SORT(x) sort(x.begin(),x.end())
#define SORTR(x) sort(x.begin(),x.end(),greater<int>())

#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple

using namespace std;
using ll = long long;

// -----------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------

// O(sqrt(n)) complexity check
bool isPrime(ll n){
    if (n==2) return true;
    if (n%2==0) return false;
    for(ll p = 3LL; p*p <= n; p+=2LL){
        if (n%p==0) return false;
    }
    return true;
}

struct Sieve {
    int n;
    // f[x] = largest prime that divides x
    // x:     0  1  2  3 4  5 6  7 8 9 10 11 12 13 14
    // f[x]: -1 -1 -1 -1 2 -1 3 -1 2 3  5 -1  3 -1  7 
    vector<int> f;
    Sieve(int n): n(n), f(n,-1) {
        for (int i = 2; i < n; i++){
            if (f[i] == -1){
                for (int j = i * 2; j < n; j += i){
                    f[j] = i;
                }
            }
        }
    }

    // checks if x is prime or not
    bool isPrime(int x) { return f[x] == x;}

    // returns all primes that divide x: O(log(x))
    set<int> getPrimes(int x) {
        set<int> p;
        while (f[x] != -1){
            p.insert(f[x]);
            x /= f[x];
        }
        if (x > 1){
            p.insert(x);
        }
        return p;
    }

    // returns all primes that divide x and their power degrees: O(log(x))
    vector<pair<int,int>> factor(int x){
        set<int> pr = getPrimes(x);
        vector<pair<int,int>> ret;
        for(auto& p: pr){
            int power = 0;
            while(x%p==0){
                x/=p;
                power++;
            }
            ret.emplace_back(p,power);
        }
        return ret;
    }
} sieve(1e7);

// -----------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------


void solve(){
    int x = 121231;
    cout << "Primes of " << x << " is: [ ";
    for(auto e: sieve.getPrimes(x)){
        cout << e << " ";
    }
    cout << "]\n";
    cout << x << ": ";
    for(auto e: sieve.factor(x)){
        cout << e.first << "^" << e.second << " ";
    }
}


int main() {
    solve();
}












