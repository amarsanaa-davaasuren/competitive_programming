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
using LL = long long;

typedef std::pair<int, int> pii;
typedef std::pair<int, double> pid;
typedef std::vector<int> vi;
typedef std::vector<pii> vii;

const double PI = 3.14159265358979323846264338327950L;
const int mod = 998244353;
const ll INF = 1LL<<60;

int dep[114514];
int par[114514][19];
vector<int> gr[114514]; // graph

void dfs(int v,int u,int d){ // node parent depth
	dep[v]=d;
	for(auto w: gr[v]){
        if(w==u) continue;
		par[w][0]=v;
        dfs(w,v,d+1);
	}
}
int lcp(int a,int b){
	if(dep[a]<dep[b]) swap(a,b); // aが深い
    int da = dep[a];
	rep(i,19){
		if (((da-dep[b])&(1<<i))) a=par[a][i];
	}
	if(a==b) return a;
	for(int i=18;i>=0;i--){
		if(par[a][i]!=par[b][i]) a=par[a][i],b=par[b][i];
	}
	return par[a][0];
}

void solve()
{
	int n,q,x,y;
	cin>>n;
	rep(i,n-1){
		cin>>x>>y;x--;y--;gr[x].pb(y);gr[y].pb(x);
	}
	memset(par,0,sizeof(par));
	dfs(0,-1,0); // node, parent, depth
    
	rep(i,18) rep(j,n) par[j][i+1]=par[par[j][i]][i];
    
	cin>>q;
	rep(i,q){
		cin>>x>>y;x--;y--;
		cout<<dep[x]+dep[y]-2*dep[lcp(x,y)]+1<<endl;
	}
}


int main() {
    int T = 1;
    // cin >> T;
    
    while (T--) {
        solve();
        cout << endl;
    }
}
