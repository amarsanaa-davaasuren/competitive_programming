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
} comb(100100);

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



struct binary_trie {
    using val_type = int;
    static constexpr int k = 8 * sizeof(val_type);
 
    struct Node {
        unsigned int count = 0;
        int idx[2] = {-1, -1};
    };
    std::vector<Node> d{{}};
 
    void add(val_type x) {
        int now = 0;
        d[0].count++;
        for(int i = k - 1; i >= 0; i--) {
            bool bit = x >> i & 1;
            if (d[now].idx[bit] == -1) {
                d[now].idx[bit] = d.size();
                d.emplace_back();
            }
            now = d[now].idx[bit];
            d[now].count++;
        }
    }
 
    val_type xor_max(val_type x) {
        assert(d[0].count);
        int now = 0;
        val_type z = 0;
        for(int i = k - 1; i >= 0; i--) {
            bool bit = !(x >> i & 1);
            if (d[now].idx[bit] == -1) bit = !bit;
            z = z << 1 | bit;
            now = d[now].idx[bit];
        }
        return x ^ z;
    }
};


void solve(){
    int n,k;
    cin >> n >> k;

    vector<ll> a(n);
    rep(i,n) cin >> a[i];
    unordered_map<ll,vector<ll>> mp;
    
    if (k==0){
        cout << n << endl;
        rep(i,n) cout << i + 1 << " "; 
        return;
    }

    int msb = 0;
    rep(i,31) if ((k>>i)%2) msb = i;
    rep(i,n){
        mp[(a[i]>>(msb+1))].pb(i);
    }

    vector<int> ret;

    for(auto& [val,values]:mp){
        binary_trie bt;
        for(auto id:values){
            bt.add(a[id]);
        }
        bool f = 0;
        for(auto id:values){
            if (!f && bt.xor_max(a[id]) >= k){
                f = 1;
                ret.pb(id);
                for(auto id2:values){
                    if ((a[id]^a[id2]) >= k){
                        ret.pb(id2);
                        break;
                    }
                }
            }
        }
        if (!f){
            ret.pb(values[0]);
        }
    }

    if (ret.size()<=1){
        cout << -1 << endl;
        return;
    }

    cout << ret.size() << endl;
    for(auto e: ret){
        cout << e + 1 << " ";
    }
    
    

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

