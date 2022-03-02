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


#ifndef ATCODER_LAZYSEGTREE_HPP
#define ATCODER_LAZYSEGTREE_HPP 1

// #include "atcoder/internal_bit"
#ifndef ATCODER_INTERNAL_BITOP_HPP
#define ATCODER_INTERNAL_BITOP_HPP 1

#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace atcoder {

namespace internal {

// @param n `0 <= n`
// @return minimum non-negative `x` s.t. `n <= 2**x`
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

// @param n `1 <= n`
// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
int bsf(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

}  // namespace internal

}  // namespace atcoder

#endif  // ATCODER_INTERNAL_BITOP_HPP

namespace atcoder {

template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segtree {
  public:
    lazy_segtree() : lazy_segtree(0) {}
    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    explicit lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {
        log = internal::ceil_pow2(_n);
        size = 1 << log;
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push(r >> i);
        }

        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
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

    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
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
    std::vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) {
            lz[k] = composition(f, lz[k]);
            if (d[k].fail) push(k), update(k);  // MODIFIED!!!
        }
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};

}  // namespace atcoder

#endif  // ATCODER_LAZYSEGTREE_HPP

/////////////////////////////////////////////////////// ACL ここまで ///////////////////////////////////////////////////////

namespace RangeUpdateChgcd_RangeMaxSum {

constexpr uint32_t BINF = 1 << 30;
struct S {
    uint32_t max;    // 区間最大値
    uint32_t lcm;    // min(BINF, (区間内全要素の最大公約数))
    uint32_t sz;     // 区間要素数
    uint64_t sum;    // 区間内全要素の総和
    bool fail;
    S() : max(0), lcm(1), sz(0), sum(0), fail(0) {}
    S(uint32_t x, uint32_t sz_ = 1) : max(x), lcm(x), sz(sz_), sum((uint64_t)x * sz_), fail(0) {}
};

S e() { return S(); }

S op(S l, S r) {
    if (r.sz == 0) return l;
    if (l.sz == 0) return r;
    S ret;
    ret.max = std::max(l.max, r.max);
    ret.sum = l.sum + r.sum;
    ret.lcm = std::min(uint64_t(BINF), (uint64_t)l.lcm * r.lcm / std::__gcd(l.lcm, r.lcm));
    ret.sz = l.sz + r.sz;
    return ret;
}

struct F {
    uint32_t dogcd, reset;
    F() : dogcd(0), reset(0) {}
    F(uint32_t g, uint32_t upd) : dogcd(g), reset(upd) {}
    static F gcd(uint32_t g) noexcept { return F(g, 0); }
    static F update(uint32_t a) noexcept { return F(0, a); }
};

F composition(F fnew, F fold) {
    if (fnew.reset) return F::update(fnew.reset);
    else if (fold.reset) {
        return F::update(std::__gcd(fnew.dogcd, fold.reset));
    } else {
        return F::gcd(std::__gcd(fnew.dogcd, fold.dogcd));
    }
}

F id() { return F(); }

S mapping(F f, S x) {
    if (x.fail) return x;
    if (f.reset) x = S(f.reset, x.sz);
    if (f.dogcd) {
        if (x.sz == 1) {
            x = S(std::__gcd(x.max, f.dogcd));
        } else if (x.lcm == BINF or f.dogcd % x.lcm) {
            // 区間 gcd クエリによって，複数個の要素からなる区間で
            // いずれかの値が変更を受ける場合のみ計算失敗
            x.fail = true;
        }
    }
    return x;
}
using segtree = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
} // namespace RangeUpdateChgcdRangeMaxSum


namespace RangeBitwiseAndOrRangeMax {
using UINT = uint32_t;
constexpr UINT digit = 20;
constexpr int mask = (1 << digit) - 1;

struct S {
    UINT max;    // 区間最大値
    UINT upper;  // 区間内全要素の bitwise or
    UINT lower;  // 区間内全要素の bitwise and
    bool fail;
    S(UINT x = 0) : max(x), upper(x), lower(x), fail(false) {}
};

S e() { return S(); }

S op(S l, S r) {
    l.max = std::max(l.max, r.max);
    l.upper |= r.upper;
    l.lower &= r.lower;
    return l;
}

struct F {
    UINT bit_and;
    UINT bit_or;
    F() : bit_and(mask), bit_or(0) {}
    F(UINT a, UINT o) : bit_and(a), bit_or(o) {}
    static F b_and(UINT a) noexcept { return {a, 0}; }
    static F b_or(UINT a) noexcept { return {mask, a}; }
};

F composition(F fnew, F fold) {
    return F{fnew.bit_and & fold.bit_and, fnew.bit_or | (fnew.bit_and & fold.bit_or)};
}

F id() { return F(); }

S mapping(F f, S x) {
    if ((x.upper - x.lower) & (~f.bit_and | f.bit_or)) {
        // 区間内で立っている要素と立っていない要素が混在するような bit で
        // 変更が起きた場合のみ計算失敗（新たな最大値が不明なので）
        x.fail = true;
        return x;
    }
    x.upper = (x.upper & f.bit_and) | f.bit_or;
    x.lower = (x.lower & f.bit_and) | f.bit_or;
    x.max = (x.max & f.bit_and) | f.bit_or;
    return x;
}
using segtree = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
} // namespace RangeBitwiseAndOrRangeMax


namespace RangeChMinMaxAddSum {
template <typename Num> inline Num second_lowest(Num a, Num a2, Num c, Num c2) noexcept {
    // a < a2, c < c2 のとき全引数を昇順ソートして二番目の値
    return a == c ? std::min(a2, c2) : a2 <= c ? a2 : c2 <= a ? c2 : std::max(a, c);
}
template <typename Num> inline Num second_highest(Num a, Num a2, Num b, Num b2) noexcept {
    // a > a2, b > b2 のとき全引数を降順ソートして二番目の値
    return a == b ? std::max(a2, b2) : a2 >= b ? a2 : b2 >= a ? b2 : std::min(a, b);
}

using BNum = long long;
constexpr BNum BINF = 1LL << 61;

struct S {
    BNum lo, hi, lo2, hi2, sum;  // 区間最小・最大値，区間最小・最大から二番目の値，区間総和
    unsigned sz, nlo, nhi;       // 区間要素数，区間最小・最大値をとる要素の個数
    bool fail;
    S() : lo(BINF), hi(-BINF), lo2(BINF), hi2(-BINF), sum(0), sz(0), nlo(0), nhi(0), fail(0) {}
    S(BNum x, unsigned sz_ = 1)
        : lo(x), hi(x), lo2(BINF), hi2(-BINF), sum(x * sz_), sz(sz_), nlo(sz_), nhi(sz_), fail(0) {}
};

S e() { return S(); }

S op(S l, S r) {
    S ret;
    ret.lo = std::min(l.lo, r.lo), ret.hi = std::max(l.hi, r.hi);
    ret.lo2 = second_lowest(l.lo, l.lo2, r.lo, r.lo2);
    ret.hi2 = second_highest(l.hi, l.hi2, r.hi, r.hi2);
    ret.sum = l.sum + r.sum, ret.sz = l.sz + r.sz;
    ret.nlo = l.nlo * (l.lo <= r.lo) + r.nlo * (r.lo <= l.lo);
    ret.nhi = l.nhi * (l.hi >= r.hi) + r.nhi * (r.hi >= l.hi);
    return ret;
}

struct F {
    BNum lb, ub, bias;
    F(BNum chmax_ = -BINF, BNum chmin_ = BINF, BNum add = 0) : lb(chmax_), ub(chmin_), bias(add) {}
    static F chmin(BNum x) noexcept { return F(-BINF, x, BNum(0)); }
    static F chmax(BNum x) noexcept { return F(x, BINF, BNum(0)); }
    static F add(BNum x) noexcept { return F(-BINF, BINF, x); };
};

F composition(F fnew, F fold) {
    F ret;
    ret.lb = std::max(std::min(fold.lb + fold.bias, fnew.ub), fnew.lb) - fold.bias;
    ret.ub = std::min(std::max(fold.ub + fold.bias, fnew.lb), fnew.ub) - fold.bias;
    ret.bias = fold.bias + fnew.bias;
    return ret;
}

F id() { return F(); }

S mapping(F f, S x) {
    if (x.sz == 0) return e();
    else if (x.lo == x.hi or f.lb == f.ub or f.lb >= x.hi or f.ub < x.lo) {
        return S(std::min(std::max(x.lo, f.lb), f.ub) + f.bias, x.sz);
    } else if (x.lo2 == x.hi) {
        x.lo = x.hi2 = std::max(x.lo, f.lb) + f.bias;
        x.hi = x.lo2 = std::min(x.hi, f.ub) + f.bias;
        x.sum = x.lo * x.nlo + x.hi * x.nhi;
        return x;
    } else if (f.lb < x.lo2 and f.ub > x.hi2) {
        BNum nxt_lo = std::max(x.lo, f.lb), nxt_hi = std::min(x.hi, f.ub);
        x.sum += (nxt_lo - x.lo) * x.nlo - (x.hi - nxt_hi) * x.nhi + f.bias * x.sz;
        x.lo = nxt_lo + f.bias, x.hi = nxt_hi + f.bias, x.lo2 += f.bias, x.hi2 += f.bias;
        return x;
    }
    x.fail = 1;
    return x;
}
using segtree = atcoder::lazy_segtree<S, op, e, F, mapping, composition, id>;
} // namespace RangeChMinMaxAddSum



void solve() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    uint32_t N, Q;
    cin >> N >> Q;
    vector<RangeUpdateChgcd_RangeMaxSum::S> A(N);
    for (auto &a : A) {
        uint32_t tmp;
        cin >> tmp, a = {tmp, 1};
    }

    RangeUpdateChgcd_RangeMaxSum::segtree segtree(A);
    uint32_t q, l, r, x;
    while (Q--) {
        cin >> q >> l >> r;
        l--;
        if (q <= 2) {
            cin >> x;
            if (q == 1) segtree.apply(l, r, RangeUpdateChgcd_RangeMaxSum::F::update(x));
            if (q == 2) segtree.apply(l, r, RangeUpdateChgcd_RangeMaxSum::F::gcd(x));
        } else {
            auto v = segtree.prod(l, r);
            if (q == 3) cout << v.max << '\n';
            if (q == 4) cout << v.sum << '\n';
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




