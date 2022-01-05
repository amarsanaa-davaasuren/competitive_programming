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
#define chmin(x,y) x = min(x, y)
#define chmax(x,y) x = max(x, y)

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
const ll INFLL = 1LL<<61;
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
} comb(2002);

struct Node {
    int val;
    Node* next;
    Node* prev;
    Node(int val = 0) : val(val),next(nullptr), prev(nullptr) {}
};


struct Edge{    
    int to,id;
    Edge(int to, int id):to(to),id(id){}
};

struct maxStack {
    stack<ll> a, mx;
    ll getMax() { return mx.size() ? mx.top() : 0;}
    void push(ll x) {
        a.push(x);
        mx.push(max(x, getMax()));
    }
    ll top() { assert(a.size()); return a.top();}
    void pop() { a.pop(); mx.pop();}
    int size() { return a.size();}
};
struct maxQueue {
    maxStack s, t;
    void mv() {
        while (t.size()) {
            s.push(t.top());
            t.pop();
        }
    }
    void push(ll x) { t.push(x);}
    void pop() {
    if (!s.size()) mv();
        s.pop();
    }
    ll getMax() {
        return max(s.getMax(), t.getMax());
    }
};


void solve(){
    
    int h,w,h1,w1,h2,w2;
    cin >> h >> w >> h1 >> w1 >> h2 >>  w2;
    h2 = min(h2,h1);
    w2 = min(w2,w1);
    vector a(h+1,vector<ll>(w+1,0));
    rep(i,h) rep(j,w) cin >> a[i+1][j+1];

    rep(i,h+1) rep(j,w) a[i][j+1] += a[i][j];
    rep(i,h) rep(j,w+1) a[i+1][j] += a[i][j];

    auto sum = [&](int i, int j, int h, int w){
        ll ret = a[i+h][j+w];
        ret -= a[i][j+w];
        ret -= a[i+h][j];
        ret += a[i][j];
        return ret;
    };
    

    
    vector a2(h-h2+1,vector<ll>(w-w2+1));
    rep(i,h-h2+1){
        rep(j,w-w2+1){
            ll v = sum(i,j,h2,w2);
            a2[i][j] = v; 
        }
    }

    vector a3(h-h2+1,vector<ll>(w-w1+1));
    rep(i,h-h2+1) {
        maxQueue q;
        rep(j,w1-w2+1) q.push(a2[i][j]);
        rep(j,w-w1+1) {
            if (j) {
                q.push(a2[i][w1-w2+j]);
                q.pop();
            }
            a3[i][j] = q.getMax();
        }
    }

    vector a4(h-h1+1,vector<ll>(w-w1+1));
    rep(j,w-w1+1) {
        maxQueue q;
        rep(i,h1-h2+1) q.push(a3[i][j]);
        rep(i,h-h1+1) {
            if (i) {
                q.push(a3[h1-h2+i][j]);
                q.pop();
            }
            a4[i][j] = q.getMax();
        }
    }

    ll ans = 0;
    rep(i,h-h1+1)rep(j,w-w1+1) {
        ll now = sum(i,j,h1,w1);
        now -= a4[i][j];
        chmax(ans,now);
    }
    cout << ans;

}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int T = 1;
    // cin >> T;
    for(int t = 1; t <=T ; t++){
        // cout << "Case #" << t << ": ";
        solve();
        // cout << endl;
    }
}
