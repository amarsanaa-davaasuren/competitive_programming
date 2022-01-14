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
using LL = long long;

typedef std::pair<int, int> pii;
typedef std::pair<int, double> pid;
typedef std::vector<int> vi;
typedef std::vector<pii> vii;

const double PI = 3.14159265358979323846264338327950L;
const int mod = 1e9+7;


bool is_prime(ll n){
    if (n==2) return true;
    if (n%2==0) return false;
    for(ll p = 3LL; p*p <= n; p+=2LL){
        if (n%p==0) return false;
    }
    return true;
}

struct Sieve{
    int NMAX;
    vector<vector<pair<int,int>>> fac;
    vector<int> f, primes;

    Sieve(int NMAX=1):NMAX(NMAX), f(NMAX+1) {
        f[0] = f[1] = -1;
        for (ll i = 2; i <= NMAX; ++i) {
            if (f[i]) continue;
            primes.push_back(i);
            f[i] = i;
            for (ll j = i*i; j <= NMAX; j += i) {
                if (!f[j]) f[j] = i;
            }
        }
    }
    
    void factorize(){
        fac.resize(NMAX);
        int p = 2;
        while(p<NMAX){
            int cur = p;
            fac[cur].pb({p,1});
            while(cur+p < NMAX){
                cur += p;
                int power = 0;
                int tmp = cur;
                while(tmp%p==0){
                    power++;
                    tmp /= p;
                }
                fac[cur].pb({p,power});
            }
            while(p < NMAX && fac[p].size() != 0){
                p++;
            }
        }
    }
};


struct Sieve {
  int n;
  vector<int> f, primes;
  Sieve(int n=1):n(n), f(n+1) {
    f[0] = f[1] = -1;
    for (ll i = 2; i <= n; ++i) {
      if (f[i]) continue;
      primes.push_back(i);
      f[i] = i;
      for (ll j = i*i; j <= n; j += i) {
        if (!f[j]) f[j] = i;
      }
    }
  }
  bool isPrime(int x) { return f[x] == x;}
  vector<int> factorList(int x) {
    vector<int> res;
    while (x != 1) {
      res.push_back(f[x]);
      x /= f[x];
    }
    return res;
  }
  vector<pair<ll,int>> factorL(ll x) {
    vector<pair<ll,int>> res;
    for (int p : primes) {
      int y = 0;
      while (x%p == 0) x /= p, ++y;
      if (y != 0) res.emplace_back(p,y);
    }
    if (x != 1) res.emplace_back(x,1);
    return res;
  }
} prime(33000);




void solve(){
    Sieve sieve(100101);
    cout << sieve.primes.size() << endl;
    // for(auto e:sieve.primes) cout << e << " ";
    // cout << endl;

    // sieve.factorize();
    // rep(i,100){
    //     cout << i << "=";
    //     for(auto e: sieve.fac[i]){
    //         cout << e.first << "^" << e.second <<" ";
    //     }
    //     cout << endl;
    // }
}


int main() {
    int T = 1;
    // cin >> T;

    while (T--) {
        solve();
        // cout << endl;
    }
}












