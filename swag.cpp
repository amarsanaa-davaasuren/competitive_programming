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
#define chmin(x,y) x = min(x, y)
#define chmax(x,y) x = max(x, y)

using namespace std;
using ll = long long;
using LL = long long;
using comp = complex<long double>;

typedef std::pair<int, int> pii;
typedef std::pair<int, double> pid;
typedef std::vector<int> vi;
typedef std::vector<pii> vii;

const double PI = 3.14159265358979323846264338327950L;

int mod = 998244353;
const ll INFLL = 1LL<<61;
const int INF = 1<<30;


// -----------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------

struct maxStack {
    stack<ll> nums, maxs;
    ll getMax() { 
        if (maxs.size() != 0) return maxs.top();
        return -INFLL;
    }
    void push(ll num){
        nums.push(num);
        maxs.push(max(num, getMax()));
    }
    ll top() { 
        assert(nums.size());
        return nums.top();
    }
    void pop() { 
        nums.pop(); 
        maxs.pop();
    }
    int size() {
        return nums.size();
    }
};

struct minStack {
    stack<ll> nums, mins;
    ll getMin() { 
        if (mins.size() != 0) return mins.top();
        return INFLL;
    }
    void push(ll num){
        nums.push(num);
        mins.push(min(num, getMin()));
    }
    ll top() { 
        assert(nums.size());
        return nums.top();
    }
    void pop() { 
        nums.pop(); 
        mins.pop();
    }
    int size() {
        return nums.size();
    }
};

struct maxQueue {
    maxStack left, right;
    minStack leftMin, rightMin;
    void mv() {
        while (right.size()) {
            left.push(right.top());
            right.pop();
        }
        while (rightMin.size()) {
            leftMin.push(rightMin.top());
            rightMin.pop();
        }
    }
    void push(ll num) { 
        right.push(num);
        rightMin.push(num);
    }
    void pop() {
        if (!left.size()) mv();
        left.pop();
        if (!leftMin.size()) mv();
        leftMin.pop();
    }
    ll getMax() {
        return max(left.getMax(), right.getMax());
    }
    ll getMin() {
        return min(leftMin.getMin(), rightMin.getMin());
    }
    int size(){
        return left.size() + right.size();
    }
};

// -----------------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------------


void solve(){
    maxQueue q;
    vector<int> v = {1,2,3,4,-1,1,2,3,1};
    cout << "Adding values: ";
    for(auto e:v) q.push(e), cout << e << " ";
    cout << "\n";

    cout << "Get max/min and pop the left most value:\n";
    cout << "   max: " << q.getMax() << " min: " << q.getMin() << "\n";
    q.pop();
    cout << "   max: " << q.getMax() << " min: " << q.getMin() << "\n";
    q.pop();
    cout << "   max: " << q.getMax() << " min: " << q.getMin() << "\n";
    q.pop();
    cout << "   max: " << q.getMax() << " min: " << q.getMin() << "\n";
    q.pop();
    cout << "   max: " << q.getMax() << " min: " << q.getMin() << "\n";
    q.pop();
    cout << "   max: " << q.getMax() << " min: " << q.getMin() << "\n";

    cout << "Add 6 and the max/min is:\n";
    q.push(6);
    cout << "   max: " << q.getMax() << " min: " << q.getMin() << "\n";
    
}

int main(){
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int T = 1;
    // cin >> T;
    for(int t = 1; t <=T ; t++){
        // cout << "Case #" << t << ": ";
        solve();
        // cout << endl;
    }
}

