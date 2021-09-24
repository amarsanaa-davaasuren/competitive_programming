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

//#include <bits/stdc++.h>
#define maxs(x,y) x = max(x,y)
#define mins(x,y) x = min(x,y)
#define rep(i,n) for(int (i)=0;(i)<(n);(i)++)
#define repr(i, n) for (int i = (n) - 1; i >= 0; i--)
#define FOR(i,i0,n) for(int (i)=(i0);(i)<(n);(i)++)
#define FORR(i,i0,n) for(int (i)=(n)-1; (i)>=(i0);(i)--)
#define SORT(x) sort(x.begin(),x.end())
#define SORTR(x) sort(x.begin(),x.end(),greater<int>())

#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple

using namespace std;
using ll = long long;
using LL = long long;

typedef std::pair<int, int> pii;
typedef std::pair<int, double> pid;
typedef std::vector<int> vi;
typedef std::vector<pii> vii;

const double PI = 3.14159265358979323846264338327950L;
const int mod = 1e9+7;
const int NMAX = 1001000;


bool is_prime(ll n){
    if (n==2) return true;
    if (n%2==0) return false;
    for(ll p = 3LL; p*p <= n; p+=2LL){
        if (n%p==0) return false;
    }
    return true;
}



void solve(){

    vector<vector<pair<int,int>>> cnt(NMAX,vector<pair<int,int>>());
    int p = 2;
    
    while(p<NMAX){
        int cur = p;
        cnt[cur].pb({p,1});
        while(cur+p < NMAX){
            cur += p;
            int power = 0;
            int tmp = cur;
            while(tmp%p==0){
                power++;
                tmp /= p;
            }
            cnt[cur].pb({p,power});
        }
        while(p < NMAX && cnt[p].size() != 0){
            p++;
        }
    }
    
    
    rep(i,101){
        cout << i << endl;
        for(auto e:cnt[i]) cout << e.first << "~" << e.second << " ";
        cout << endl;
    }
}

int main() {
    int T = 1;
    // cin >> T;

    while (T--) {
        solve();
        // cout << endl;
    }
}












