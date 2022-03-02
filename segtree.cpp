

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

//#include <bits/stdc++.h>
#define maxs(x,y) x = max(x,y)
#define mins(x,y) x = min(x,y)
#define rep(i,n) for(int (i)=0;(i)<(n);(i)++)
#define repr(i, n) for (int i = (n) - 1; i >= 0; i--)
#define FOR(i,i0,n) for(int (i)=(i0);(i)<(n);(i)++)
#define FORR(i,i0,n) for(int (i)=(n)-1; (i)>=(i0);(i)--)
#define SORT(x) sort(x.begin(),x.end())
#define SORTR(x) sort(x.begin(),x.end(),greater<vector<int>>())

#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple

using namespace std;
using ll = long long;
typedef std::pair<int, int> pii;
typedef std::pair<int, double> pid;
typedef std::vector<int> vi;
typedef std::vector<pii> vii;

#define PI 3.14159265358979323846264338327950L
const int mod = 998244353;


// -----------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------

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
    ll val;
    SGT(ll val):val(val){}
};
const int SID = 1e9;
SGT e() {
    return SGT(SID);
};
SGT opMax(SGT a, SGT b) {
    // if a or b is an unit element return the other one
    if (a.val == e().val) return b;
    if (b.val == e().val) return a;

    if (a.val > b.val) return a;
    return b;
};

SGT opMin(SGT a, SGT b) {
    // if a or b is an unit element return the other one
    if (a.val == e().val) return b;
    if (b.val == e().val) return a;

    if (a.val < b.val) return a;
    return b;
};

SGT opXor(SGT a, SGT b) {
    // if a or b is an unit element return the other one
    if (a.val == e().val) return b;
    if (b.val == e().val) return a;

    return {a.val^b.val};
};


// -----------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------

void solve(){
    vector<int> ind = {0,1,3,54};
    vector<int> values = {4,2,5,-190};
    int n = ind.size();
    {
        cout << "segtree that finds max" << "\n";
        segtree<SGT, opMax, e> seg(1001);
        for(int i = 0; i < n; i++){
            seg.set(ind[i],values[i]);
        }
        auto ans = seg.prod(0,100);
        cout << ans.val << "\n";
    }

    {
        cout << "segtree that finds min" << "\n";
        segtree<SGT, opMin, e> seg(1001);
        for(int i = 0; i < n; i++){
            seg.set(ind[i],values[i]);
        }
        auto ans = seg.prod(0,100);
        cout << ans.val << "\n";
    }

    {
        cout << "segtree that finds xor" << "\n";
        segtree<SGT, opXor, e> seg(1001);
        for(int i = 0; i < n; i++){
            seg.set(ind[i],values[i]);
        }
        auto ans = seg.prod(0,10);
        cout << ans.val << "\n";
    }
}

int main() {
    solve();
}
