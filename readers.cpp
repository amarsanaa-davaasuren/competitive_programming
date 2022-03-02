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

vector<vector<int>> readGraph(int n, int m=-1){
    if (m==-1) m = n-1;
    vector graph = vector<vector<int>>(n,vector<int>());
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--;b--;
        graph[a].pb(b);
        graph[b].pb(a);
    }
    return graph;
}

vector<vector<int>> readDirectedGraph(int n, int m=-1){
    if (m==-1) m = n-1;
    vector graph = vector<vector<int>>(n,vector<int>());
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a--;b--;
        graph[a].pb(b);
    }
    return graph;
}


// -----------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------


void solve(){

}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int T = 1;
    
//     cin >> T;
    for(int t = 1; t <=T ; t++){
        // cout << "Case #" << t << ": ";
        solve();
        // cout << endl;
    }
}

