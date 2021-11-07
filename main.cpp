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
// #include <bits/stdc++.h>
#include <complex>

#define maxs(x,y) x = max(x,y)
#define mins(x,y) x = min(x,y)
#define rep(i,n) for(int i=0;(i)<(n);(i)++)
#define repr(i, n) for (int i = (n) - 1; i >= 0; i--)
#define FOR(i,i0,n) for(int (i)=(i0);(i)<(n);(i)++)
#define FORR(i,i0,n) for(int (i)=(n)-1; (i)>=(i0);(i)--)
#define SORT(x) sort(x.begin(),x.end())
#define SORTR(x) sort(x.begin(),x.end(),greater<int>())
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mt make_tuple

using namespace std;
using ll = long long;
using LL = long long;
using comp = complex<long double>;

typedef std::pair<int, int> pii;
typedef std::pair<int, double> pid;
typedef std::vector<int> vi;
typedef std::vector<pii> vii;

const double PI = 3.14159265358979323846264338327950L;

int mod = 998244353;
const ll INFLL = 1LL<<62;
const int INF = 1<<30;

comp inC(){
    double x,y;
    cin >> x >> y;
    return {x,y};
}



void tle(){
    rep(i,2002002002002) continue;
}

struct mint {
    ll x; // typedef long long ll;
    mint(ll x=0):x((x%mod+mod)%mod){}
    mint operator-() const { return mint(-x);}
    mint& operator+=(const mint a) {
    if ((x += a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator-=(const mint a) {
    if ((x += mod-a.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator*=(const mint a) { (x *= a.x) %= mod; return *this;}
    mint operator+(const mint a) const { return mint(*this) += a;}
    mint operator-(const mint a) const { return mint(*this) -= a;}
    mint operator*(const mint a) const { return mint(*this) *= a;}
    mint pow(ll t) const {
    if (!t) return 1;
    mint a = pow(t>>1);
    a *= a;
    if (t&1) a *= *this;
        return a;
    }

    // for prime mod
    mint inv() const { return pow(mod-2);}
    mint& operator/=(const mint a) { return *this *= a.inv();}
    mint operator/(const mint a) const { return mint(*this) /= a;}
};
istream& operator>>(istream& is, mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}
struct combination {
  vector<mint> fact, ifact;
  combination(int n):fact(n+1),ifact(n+1) {
    assert(n < mod);
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) fact[i] = fact[i-1]*i;
    ifact[n] = fact[n].inv();
    for (int i = n; i >= 1; --i) ifact[i-1] = ifact[i]*i;
  }
  mint operator()(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n]*ifact[k]*ifact[n-k];
  }
} comb(202);


vector<int> g[200200];
tuple<int,int,int> V[200200];

void solve(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int n,m,q;
    cin >> n >> m >> q;
    
    rep(i,m){
        int u,v;
        cin >> u >> v;
        u--;v--;
        g[u].pb(v);
        g[v].pb(u);
    }
    rep(i,n) V[i] = {i+1,0,0}; // value, last time updated, need to propagated

    rep(i,q){
        int x;
        cin >> x;
        x--;
        auto [v,t,f] = V[x];

        if (g[x].size() < sqrt(n)){
            int lt = t, lind = x;
            for(auto e:g[x]){
                if (g[e].size() < sqrt(n)) continue;
                auto [ev,et,ef] = V[e];
                if (!ef || et < lt) continue;
                lt = et;
                lind = e;
            }
            v = get<0>(V[lind]);

            for(auto e:g[x]){
                if (g[e].size() < sqrt(n)){
                    V[e] = {v,i+1,0};
                }
                else{
                    auto [ev,et,ef] = V[e];
                    if (!ef) continue;
                    lt = et;
                    lind = e;
                }
            }
        }
        else{
            V[x] = {v,i+1,1};
        }
    }
}   





int main() {
    int T = 1;
    // cin >> T;
    while (T--) {
        solve();
    }
}



