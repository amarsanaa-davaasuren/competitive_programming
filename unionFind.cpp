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


// -----------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------

// union by size + path having
class UnionFind {
public:
    int n;
    // parent id
    vector <ll> par;
    // union size
    vector <ll> siz;

    // Constructor
    UnionFind(ll n): n(n), par(n), siz(n, 1LL) {
        // initially each element is its own parent
        for (ll i = 0; i < n; ++i) par[i] = i; 
    }

    // initialize each element as its own parent
    void init(ll m) {
        n = m;
        par.resize(n);
        siz.assign(n, 1LL); 
        for (ll i = 0; i < n; ++i) par[i] = i; 
    }

    // Find its root id
    ll root(ll x) { //
        if (par[x] == x) return x;
        // make x's grand parent its parent
        return par[x] = par[par[x]];
    }

    // Merge two elements
    bool merge(ll x, ll y) {
        x = root(x);
        y = root(y);
        if (x == y) return false;
        // merge technique (merge smaller y to the larger x)
        if (siz[x] < siz[y]) swap(x, y);
        siz[x] += siz[y];
        par[y] = x;
        return true;
    }

    // check if two elements belong to the same group
    bool isSame(ll x, ll y) { // 連結判定
        return root(x) == root(y);
    }

    // returns the size of the group
    ll size(ll x) {
        return siz[root(x)];
    }


    // returns all groups 
    map<int,vector<int>> getAllGroups(){
        map<int,vector<int>> ret;
        for(int i = 0; i < n; i++){
            int r = root(i);
            ret[r].push_back(i);
        }
        return ret;
    }
};

// -----------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------


void solve(){
    UnionFind uf = UnionFind(10);
    uf.merge(1,2);
    uf.merge(2,3);
    uf.merge(3,4);
    uf.merge(1,5);
    
    auto groups = uf.getAllGroups();
    for(auto& group: groups){
        cout << group.first << ": ";
        for(auto e: group.second) cout << e << " ";
        cout << "\n";
    }

}

int main(){
    solve();
}

