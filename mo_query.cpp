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
using P = pair<int,int>;

typedef std::pair<int, int> pii;
typedef std::pair<int, double> pid;
typedef std::vector<int> vi;
typedef std::vector<pii> vii;

const double PI = 3.14159265358979323846264338327950L;

int mod = 998244353;
const ll INFLL = 1LL << 61;
const int INF = 1 << 30;

comp inC() {
    double x, y;
    cin >> x >> y;
    return { x,y };
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


ll n,d;
multiset<ll> ms;

bool check(vector<ll>& a, ll d, ll g, int ind){
    
    vector<int> rds;
    vector<int> ads;
    
    if (ind-1 >= 0){
        int rd = a[ind]-a[ind-1]-1;
        rds.pb(rd);
    }
    if (ind+1!=n){
        int rd = a[ind+1]-a[ind]-1;
        rds.pb(rd);
    }
    if (ind == 0){
        int rd = a[ind]-1;
        ads.pb(a[ind+1]-1);
        rds.pb(rd);
    }
    
    if (ind-1 >= 0 && ind+1 != n){
        ads.pb(a[ind+1]-a[ind-1]-1);
    }
    
    
    for(auto e:ads){
        ms.insert(e);
    }
    for(auto rd:rds){
        ms.erase(ms.find(rd));
    }
    
    
    ll back = a.back();
    if (ind == n-1){
        back = a[n-2];
    }
    
    ll fr = a[0];
    if (ind == 0){
        fr = a[1];
    }
    
    int mn = *ms.begin();
    int mx = *ms.rbegin();
    
    bool ret = false;
    

    if (mx >= 2*g + 1) ret = true;
    if (d-back >= g + 1) ret = true;
    if (fr >= 2*g+2) ret = true;

    if (mn < g) ret = false;
    
    for(auto rd:rds) ms.insert(rd);
    for(auto e:ads) ms.erase(ms.find(e));
    
    return ret;
    
}


void solve(){
    int n;
    cin >> n;
    vector<int> a(n);
    rep(i,n) cin >> a[i];
    rep(i,n) a[i]--;
    
    int Q;
    cin >> Q;

    vector<int> r(Q),l(Q);
    vector<int> ans(Q);


    vector<int> q(Q);
    rep(i,Q) q[i] = i;
    rep(i,Q){
        cin >> l[i] >> r[i];
        l[i]--,r[i]--;
    }
    int D = max(1,int(n/sqrt(Q)));
    sort(begin(q),end(q),[&](int& i, int& j){
        int ri = r[i]/D, rj = r[j]/D;
        if (ri != rj) return ri < rj;
        return l[i] < l[j];
    });
    
    int nowi = -1;
    int nowj = 0;
    vector<int> cnt(n);
    int now = 0;
    auto add = [&](int i, int v){
        now -= cnt[a[i]]/2;
        cnt[a[i]] += v;
        now += cnt[a[i]]/2;
    };
    rep(i,Q){
        while(nowi>r[q[i]]) add(nowi,-1),nowi--;
        while(nowi<r[q[i]]) nowi++,add(nowi,1);

        while(nowj>l[q[i]]) nowj--,add(nowj,1);
        while(nowj<l[q[i]]) add(nowj,-1),nowj++;

        ans[q[i]] = now;
    }
    

    for(auto& e: ans) cout << e << "\n";
        
}



int main() {
    // ios::sync_with_stdio(false),cin.tie(NULL);
    int T = 1;
    // cin >> T;
    for (int t = 1; t <= T; t++) {
        // cout << "Case #" << t << ": ";
        solve();
        // cout << endl;
    }
}

