
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
typedef std::pair<int, int> pii;
typedef std::pair<int, double> pid;
typedef std::vector<int> vi;
typedef std::vector<pii> vii;

const double PI = 3.14159265358979323846264338327950L;
//const int mod = 1000000007;
const int INF = 1001001001;


// a*x + b*y = gcd(a,b) となるx,yを求める(gcd(a,b)求める。)
tuple<ll,ll,ll> extgcd(int a, int b){
    if (b==0){
        return {a,1,0};
    }
    else{
        auto [g,x,y] = extgcd(b,a%b);
        return {g,y,x-a/b*y};
    }
}


int main() {
    int a,b;
    cin >> a >> b;
    auto [g,x,y] = extgcd(a,b);
    cout << "g=" << g << ", x=" << x << ", y=" << y << endl;
    cout << "x*" << a << " + " << "y*" << b << "=" << g;
}








