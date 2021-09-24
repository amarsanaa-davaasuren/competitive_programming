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

//#include <bits/stdc++.h>
#define maxs(x,y) x = max(x,y)
#define mins(x,y) x = min(x,y)
#define rep(i,n) for(int (i)=0;(i)<(n);(i)++)
#define repr(i, n) for (int i = (n) - 1; i >= 0; i--)
#define FOR(i,i0,n) for(int (i)=(i0);(i)<(n);(i)++)
#define FORR(i,i0,n) for(int (i)=(n)-1; (i)>=(i0);(i)--)
#define SORT(x) sort(x.begin(),x.end())
#define SORTR(x) sort(x.begin(),x.end(),greater<int>())
#define rn return
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#include <time.h>
typedef std::pair<int,int> pii;
using namespace std;
using ll = long long;
#define PI 3.14159265358979323846264338327950L
const int mod =  998244353;

using bint = ll;
struct BIT{
    static const int SIZE = 100005;
	bint bit[SIZE];
    
	void init(){
        memset(bit,bint(0),sizeof(bit));
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

int main()
{
    BIT bit;
    bit.add(0,10);
    bit.add(1,2);
    bit.add(5,1);
    bit.add(6,1);
    
    ll g = bit.get(0,0);
    cout << g << endl;
    
    bit.init();
    cout << bit.get(0,2) << endl;

}


















