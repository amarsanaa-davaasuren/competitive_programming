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
#include <list>
// #include <bits/stdc++.h>
#include <complex>
#include <climits>
#include <chrono>

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
using namespace std::chrono;

using ll = long long;
using ull = unsigned long long;
using LL = long long;
using comp = complex<long double>;

typedef std::pair<ll, ll> pii;
typedef std::pair<int, double> pid;
typedef std::vector<int> vi;
typedef std::vector<pii> vii;

const double PI = 3.14159265358979323846264338327950L;

int mod = 1e9+7;
const ll INFLL = 1LL << 62;
const int INF = 1 << 30;

comp inC() {
    double x, y;
    cin >> x >> y;
    return {x,y};
}


bool is_prime(ll n) {
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (ll p = 3LL; p * p <= n; p += 2LL) {
        if (n % p == 0) return false;
    }
    return true;
}

void tle() {
    rep(i, 2002002002002) continue;
}

struct mint {
    ll x; // typedef long long ll;
    mint(ll x = 0) :x((x% mod + mod) % mod) {}
    mint operator-() const { return mint(-x); }
    mint& operator+=(const mint a) {
            if ((x += a.x) >= mod) x -= mod;
            return *this;
    }
    mint& operator-=(const mint a) {
            if ((x += mod - a.x) >= mod) x -= mod;
            return *this;
    }
    mint& operator*=(const mint a) { (x *= a.x) %= mod; return *this; }
    mint operator+(const mint a) const { return mint(*this) += a; }
    mint operator-(const mint a) const { return mint(*this) -= a; }
    mint operator*(const mint a) const { return mint(*this) *= a; }
    mint pow(ll t) const {
            if (!t) return 1;
            mint a = pow(t >> 1);
            a *= a;
            if (t & 1) a *= *this;
            return a;
    }

    // for prime mod
    mint inv() const { return pow(mod - 2); }
    mint& operator/=(const mint a) { return *this *= a.inv(); }
    mint operator/(const mint a) const { return mint(*this) /= a; }
};
istream& operator>>(istream& is, mint& a) { return is >> a.x; }
ostream& operator<<(ostream& os, const mint& a) { return os << a.x; }
struct combination {
    vector<mint> fact, ifact;
    combination(int n) :fact(n + 1), ifact(n + 1) {
            assert(n < mod);
            fact[0] = 1;
            for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i;
            ifact[n] = fact[n].inv();
            for (int i = n; i >= 1; --i) ifact[i - 1] = ifact[i] * i;
    }
    mint operator()(int n, int k) {
            if (k < 0 || k > n) return 0;
            return fact[n] * ifact[k] * ifact[n - k];
    }
} comb(100100);

struct Node {
    int val;
    Node* next;
    Node* prev;
    Node(int val = 0) : val(val), next(nullptr), prev(nullptr) {}
};

struct Edge {
    int to, id, w;
    Edge(int to, int id, int w = 1) :to(to), id(id), w(w) {}
};

struct node {
    int v;
    node* left, * right;
    node(int v, node* left, node* right) : v(v), left(left), right(right) {}
};

void bin(int x, int d = 20) {
    vector<int> p;
    while (x) {
            p.pb(x % 2);
            x /= 2;
    }
    while (int(p.size()) < d) p.pb(0);
    for (auto e : p) cout << e;
    cout << endl;
}


struct D {
    int a;
    int b;
    D(int a, int b) :a(a), b(b) {}
};



// other example (palindrome: https://codeforces.com/contest/570/submission/164909347) 
// https://codeforces.com/contest/600/problem/E
vector<int> g[100100];
map<int,int> cnt[100100];
map<int,ll> sum[100100];
int sz[100100] = {};
ll ans[100100] = {};


int merge(int to, int from){
    if (sz[to] < sz[from]) swap(to,from);
    sz[to] += sz[from];
    
    for(auto e:cnt[from]){
        int value = e.first;
        int count = e.second;
        sum[to][cnt[to][value]] -= value;
        cnt[to][value] += count;
        sum[to][cnt[to][value]] += value;
    }
    cnt[from].clear();
    sum[from].clear();
    return to;
}

int dfs(int now, int parent){
    
    int to = now;
    for(auto e:g[now]){
        if (e!=parent){
            int from = dfs(e,now);
            to = merge(to,from);
        }
    }
    
    ans[now] = (sum[to].rbegin()->second);
    return to;
}

void solve(){
    int n;
    cin >> n;
    rep(i,n){
        int v;
        cin >> v;
        cnt[i][v] = 1;
        sz[i] = 1;
        sum[i][1] += v;
    }
    rep(i,n-1){
        int u,v;
        cin >> u >> v;
        u--;v--;
        g[u].pb(v);
        g[v].pb(u);
    }
    
    dfs(0,-1);

    rep(i,n) cout << ans[i] << " ";
}


int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int T = 1;
    // cin >> T;
    for (int t = 1; t <= T; t++) {
            // cout << "Case #" << t << ": ";
            solve();
            // cout << endl;
    }
}