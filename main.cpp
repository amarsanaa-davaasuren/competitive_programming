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
using comp = complex<double>;

typedef std::pair<int, int> pii;
typedef std::pair<int, double> pid;
typedef std::vector<int> vi;
typedef std::vector<pii> vii;

const double PI = 3.14159265358979323846264338327950L;
int mod = 1e9+7;
const ll INFLL = 1LL<<62;
const int INF = 1<<30;

comp inC(){
    double x,y;
    cin >> x >> y;
    return {x,y};
}

struct Data {
    ll cost,val;
    Data(ll cost=0, ll val=0) : cost(cost), val(val){}
    bool operator<(const Data& a) const {
        return cost > a.cost;
    }
};

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
} comb(1000);

using bint = mint;
struct BIT{
    static const int SIZE = 10005;
	bint bit[SIZE];
    
	void init(){
        memset(bit,0,sizeof(bit));
    }
    
	void add(int k,bint x) {
		k++;
		while(k<SIZE){
			bit[k]+=x;
			k+=k&-k;
		}
	}
    
	bint get(int k){ // inclusive
		k++;
		bint ret=0;
		while(k>0){
			ret+=bit[k];
			k-=k&-k;
		}
		return ret;
	}
    
	bint get(int s,int t){ // inclusive 
		return get(t)-get(s-1);
	}
};

void solve() {
    // i個目まで決めて、残り n-i個の中にj個がi個目より大きい
    int n;
    string s;
    cin >> n >> s;
    int dp[4000][4000] = {};
    rep(i,4000) rep(j,4000) dp[i][j] = 1;
    cout << dp[0][0] << endl;
    BIT bit;
    rep(i,n+1){
        bit.add(i,1);
    }
    rep(ii,n-1){
        char c = s[ii];
        int i = ii+1;
        int left = (n-i);
        BIT next;
        rep(larger,left+1){
            if (c == '<'){
                next.add(larger,bit.get(larger+1,left));
            }
            else{
                next.add(larger,bit.get(0,larger));    
            }
        }
        swap(next,bit);
    }

    cout << bit.get(0,0);
    
}


int main() {
    int T = 1;
    // comb = combination(200200);
    // cin >> T;

    while (T--) {
        solve();
    }
}











