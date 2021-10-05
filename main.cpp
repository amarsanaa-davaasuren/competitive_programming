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
int mod = 998244353;
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
} comb(1000);





struct TREE{
public:
    int N;
    int bottom_node[200200];
    int parent_node[200200][22];
    int depths[200200];
    int deepest_depths[200200];
    int floor_cnts[200200];
    vector<int> graph[200200];
    vector<int> path_to_floor;
    
    TREE(int N) : N(N){}

    void read_graph(){
        rep(i,N) graph[i].clear();
        rep(i,N-1){
            int a,b;
            cin >> a >> b;
            a--;b--;
            graph[a].pb(b);
            graph[b].pb(a);
        }
    }
    
    void get_path_to_floor(int node){
        int next = bottom_node[node];
        path_to_floor.pb(node);
        if (next != -1){
            get_path_to_floor(next);
        }
    }
    
    tuple<int> get_depths(int node, int parent = -1, int depth = 0, int start_flag = 1){
        if (start_flag){
            memset(depths,-1,sizeof depths);
            memset(deepest_depths,-1,sizeof deepest_depths);
            memset(bottom_node,-1,sizeof bottom_node);
            memset(floor_cnts,-1,sizeof floor_cnts);
            memset(parent_node,-1,sizeof parent_node);
            path_to_floor.clear();
        }
        int cnt = 0;
        depths[node] = depth;
        int deepest_depth = depth;
        int next = -1;
        
        for(auto child:graph[node]){
            if (child==parent) continue;
            parent_node[child][0]=node;
            auto [child_deepest] = get_depths(child,node,depth+1,0);
            if (deepest_depth < child_deepest){
                deepest_depth = child_deepest;
                next = child;
                cnt = floor_cnts[child];
            }
            else if (deepest_depth == child_deepest){
                cnt += floor_cnts[child];
            }
        }
        
        cnt = max(cnt,1);
        bottom_node[node] = next;
        floor_cnts[node] = cnt;
        deepest_depths[node] = deepest_depth;

        if (start_flag){
            get_path_to_floor(node);
            rep(i,22) rep(j,N) parent_node[j][i+1]=parent_node[parent_node[j][i]][i];
        }
        
        return {deepest_depth};
    }

    int lca(int a,int b){
        if(depths[a]<depths[b]) swap(a,b); // aが深い
        rep(i,22){
            if ((depths[a]-depths[b])&(1<<i)){
                if (parent_node[a][i] != -1) a=parent_node[a][i];
            }
        }
        if(a==b) return a;
        for(int i=21;i>=0;i--){
            if(parent_node[a][i]!=parent_node[b][i]){
                if (parent_node[a][i] != -1) a=parent_node[a][i];
                if (parent_node[b][i] != -1) b=parent_node[b][i];
            }
        }
        if (parent_node[a][0] == -1) return a;
        return parent_node[a][0];
    }

    int get_diameter(){
        get_depths(0);
        auto [diameter] = get_depths(path_to_floor.back());
        return diameter;
    }
};





void solve(){
    int n;
    cin >> n;
    TREE tree(n);
    tree.read_graph();

    tree.get_depths(0);
    cout << tree.lca(9,10) << endl;


    int D = tree.get_diameter();
    if (D%2==0){
        int c = tree.path_to_floor[D/2];
        vector<mint> cnts;
        tree.get_depths(c);
        for(auto child:tree.graph[c]){
            if (tree.deepest_depths[child] == D/2) cnts.pb(tree.floor_cnts[child]);
        }
        
        mint ans = 1;
        for(auto e:cnts) ans *= (mint(1)+e);
        for(auto e:cnts) ans -= e;
        ans -= 1;
        cout << ans;
    }
    else{
        int a = tree.path_to_floor[D/2];
        int b = tree.path_to_floor[D/2+1];
        tree.get_depths(a,b);
        int cnt1 = 0;
        rep(i,n) cnt1 += (tree.depths[i] == D/2);
        tree.get_depths(b,a);
        int cnt2 = 0;
        rep(i,n) cnt2 += (tree.depths[i] == D/2);
        mint ans = mint(cnt1)*mint(cnt2);
        cout << ans;
    }
    cout << endl;


}



int main() {
    int T = 1;
    // cin >> T;

    while (T--) {
        solve();
    }
}











