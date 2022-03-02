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


template<typename T>
struct Matrix {
	int h, w;
	vector<vector<T>> d;
	Matrix() {}
	Matrix(int h, int w, T val=0): h(h), w(w), d(h, vector<T>(w,val)) {}
	Matrix& unit() {
		assert(h == w);
		rep(i,h) d[i][i] = 1;
		return *this;
	}
	const vector<T>& operator[](int i) const { return d[i];}
	vector<T>& operator[](int i) { return d[i];}
	Matrix operator*(const Matrix& a) const {
		assert(w == a.h);
		Matrix r(h, a.w);
		rep(i,h)rep(k,w)rep(j,a.w) {
			r[i][j] += d[i][k]*a[k][j];
		}
		return r;
	}
	Matrix pow(ll t) const {
		assert(h == w);
		if (!t) return Matrix(h,h).unit();
		if (t == 1) return *this;
		Matrix r = pow(t>>1);
		r = r*r;
		if (t&1) r = r*(*this);
		return r;
	}
};
 
void solve() {
	int h; ll w;
	cin >> h >> w;
	h = 10; w = 11;
	int n = 1<<h;
	Matrix<mint> d(n,n);
 
	rep(s,n) {
		rep(x,n) {
			if (x&s) continue;
			for (int y = x; ;y = (y-1)&x) {
				int ns = 0;
				rep(i,h) {
					if (x>>i&1) {
						if (y>>i&1) {
							ns |= 1<<i;
						} else {
							if (i == h-1) { ns = -1; break;}
							if (s>>i>>1&1) { ns = -1; break;}
							if (x>>i>>1&1) { ns = -1; break;}
						}
					}
				}
				if (ns != -1) {
					d[s][ns] += 1;
				}
				if (!y) break;
			}
		}
	}
 
	Matrix<mint> x(n,1);
	x[0][0] = 1;
	x = d.pow(w)*x;
	mint ans = x[0][0];
 
	cout << ans << endl;
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