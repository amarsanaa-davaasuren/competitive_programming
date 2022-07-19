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



namespace internal {

#ifndef _MSC_VER
template <class T>
using is_signed_int128 =
    typename std::conditional<std::is_same<T, __int128_t>::value ||
                                  std::is_same<T, __int128>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using is_unsigned_int128 =
    typename std::conditional<std::is_same<T, __uint128_t>::value ||
                                  std::is_same<T, unsigned __int128>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using make_unsigned_int128 =
    typename std::conditional<std::is_same<T, __int128_t>::value,
                              __uint128_t,
                              unsigned __int128>;

template <class T>
using is_integral = typename std::conditional<std::is_integral<T>::value ||
                                                  is_signed_int128<T>::value ||
                                                  is_unsigned_int128<T>::value,
                                              std::true_type,
                                              std::false_type>::type;

template <class T>
using is_signed_int = typename std::conditional<(is_integral<T>::value &&
                                                 std::is_signed<T>::value) ||
                                                    is_signed_int128<T>::value,
                                                std::true_type,
                                                std::false_type>::type;

template <class T>
using is_unsigned_int =
    typename std::conditional<(is_integral<T>::value &&
                               std::is_unsigned<T>::value) ||
                                  is_unsigned_int128<T>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using to_unsigned = typename std::conditional<
    is_signed_int128<T>::value,
    make_unsigned_int128<T>,
    typename std::conditional<std::is_signed<T>::value,
                              std::make_unsigned<T>,
                              std::common_type<T>>::type>::type;

#else

template <class T> using is_integral = typename std::is_integral<T>;

template <class T>
using is_signed_int =
    typename std::conditional<is_integral<T>::value && std::is_signed<T>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using is_unsigned_int =
    typename std::conditional<is_integral<T>::value &&
                                  std::is_unsigned<T>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using to_unsigned = typename std::conditional<is_signed_int<T>::value,
                                              std::make_unsigned<T>,
                                              std::common_type<T>>::type;

#endif

template <class T>
using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;

template <class T>
using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;

template <class T> using to_unsigned_t = typename to_unsigned<T>::type;

}  // namespace internal


template <class T> struct fenwick_tree {
    using U = internal::to_unsigned_t<T>;

  public:
    fenwick_tree() : _n(0) {}
    explicit fenwick_tree(int n) : _n(n), data(n) {}

    void add(int p, T x) {
        assert(0 <= p && p < _n);
        p++;
        while (p <= _n) {
            data[p - 1] += U(x);
            p += p & -p;
        }
    }

    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        return sum(r) - sum(l);
    }

  private:
    int _n;
    std::vector<U> data;

    U sum(int r) {
        U s = 0;
        while (r > 0) {
            s += data[r - 1];
            r -= r & -r;
        }
        return s;
    }
};




namespace internal {
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}
}

//segtree<SGT, op, e> seg(100100);
template <class S, S (*op)(S, S), S (*e)()> struct segtree {
  public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
    explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = internal::ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }
    
    S all_prod() const { return d[1]; }

    template <bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};


struct SGT{
    set<int> s;
    SGT(set<int>s):s(s){}
};
SGT op(SGT a, SGT b) {
    set<int> c;
    for(auto e:a.s) c.insert(e);
    for(auto e:b.s) c.insert(e);
    return SGT(c);
}
SGT e() {
    return SGT(set<int>());
}

int N = 10010;
vector<int> cnt(N,0);
vector<vector<int>> S(N,vector<int>());

void solve(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    rep(i,n) cin >> a[i];

    
    rep(i,N) cnt[i] = 0;
    rep(i,N) S[i].clear();

    rep(i,n){
        for(int p = 1; p <= k; p++){
            int v = a[i]/p;
            S[v].pb(i);
        }
    }

    set<int> SS;
    for(int i = 1; i <= 16; i++){
        SS.insert(123/i);
    }
    for(auto e:SS) cout << e << " ";
    cout << endl;
    
    int ans = 1001001001;
    int right = 0;
    int cc = 0;
    for(int left = 0; left < N; left++){
        while (right < N && cc != n) {
            for(auto e:S[right]){
                if (cnt[e] == 0) cc++;
                cnt[e]++;
            }
            right++;
        }

        if (cc == n){
            ans = min(ans,right-left-1);
        }


        for(auto e:S[left]){
            cnt[e]--;
            if (cnt[e] == 0) cc--;
        }
        if (left+1>right){
            right++;
        }
    }
    if (ans==-1) ans = 0;
    cout << ans << "\n";
}


int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int T = 1;
    cin >> T;
    for (int t = 1; t <= T; t++) {
            // cout << "Case #" << t << ": ";
            solve();
            // cout << endl;
    }
}