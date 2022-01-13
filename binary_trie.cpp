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



template<typename U = int, int B = 31>
class binary_trie {
    struct node {
        int cnt;
        node *ch[2];
        node() : cnt(0), ch{ nullptr, nullptr } {}
    };
    node* add(node* t, U val, int b = B - 1) {
        if (!t) t = new node;
        t->cnt += 1;
        if (b < 0) return t;
        bool f = (val >> (U)b) & (U)1;
        t->ch[f] = add(t->ch[f], val, b - 1);
        return t;
    }
    node* sub(node* t, U val, int b = B - 1) {
        assert(t);
        t->cnt -= 1;
        if (t->cnt == 0) return nullptr;
        if (b < 0) return t;
        bool f = (val >> (U)b) & (U)1;
        t->ch[f] = sub(t->ch[f], val, b - 1);
        return t;
    }

    U get_min(node* t, U val, int b = B - 1) const {
        assert(t);
        if (b < 0) return 0;
        bool f = (val >> (U)b) & (U)1;
        bool next;
        if (t->ch[f]) next = (f);
        else next = (1^f);
        f = (next^f);
        return get_min(t->ch[next], val, b - 1) | ((U)f << (U)b);
    }

    U get_max(node* t, U val, int b = B - 1) const {
        assert(t);
        if (b < 0) return 0;
        bool f = (val >> (U)b) & (U)1; 
        bool next;
        if (t->ch[1^f]) next = 1^f;
        else next = f;
        f = (next^f);
        return get_max(t->ch[next], val, b - 1) | ((U)f << (U)b);
    }

    U get(node* t, int k, int b = B - 1) const {
        if (b < 0) return 0;
        int m = t->ch[0] ? t->ch[0]->cnt : 0;
        return k < m ? get(t->ch[0], k, b - 1) : get(t->ch[1], k - m, b - 1) | ((U)1 << (U)b);
    }
    int count_lower(node* t, U val, int b = B - 1) {
        if (!t || b < 0) return 0;
        bool f = (val >> (U)b) & (U)1;
        return (f && t->ch[0] ? t->ch[0]->cnt : 0) + count_lower(t->ch[f], val, b - 1);
    }
    node *root;
public:
    binary_trie() : root(nullptr) {}
    int size() const {
        return root ? root->cnt : 0;
    }
    bool empty() const {
        return !root;
    }
    void insert(U val) {
        root = add(root, val);
    }
    void erase(U val) {
        root = sub(root, val);
    }
    U max_XOR_element(U bias = 0) const {
        return get_max(root, bias);
    }
    U min_XOR_element(U bias = 0) const {
        return get_min(root, bias);
    }
    int lower_bound(U val) { // return id
        return count_lower(root, val);
    }
    int upper_bound(U val) { // return id
        return count_lower(root, val + 1);
    }
    U operator[](int k) const {
        assert(0 <= k && k < size());
        return get(root, k);
    }
    int count(U val) const {
        if (!root) return 0;
        node *t = root;
        for (int i = B - 1; i >= 0; i--) {
            t = t->ch[(val >> (U)i) & (U)1];
            if (!t) return 0;
        }
        return t->cnt;
    }
};

void solve(){
    int n = 100;
    vector<int> a(n);
    rep(i,n) a[i] = rand()%20;
    SORT(a);
    for(auto e:a) cout << e << " ";
    cout << endl;
    binary_trie bt;
    for(auto e: a) bt.insert(e);

    cout << "min: " << bt.min_XOR_element() << endl;
    cout << "min we can get with xor with 21: " << bt.min_XOR_element(21) << endl;
    cout << "max we can get with xor with 21: " << bt.max_XOR_element(21) << endl;
    cout << "max: " << bt.max_XOR_element() << endl;
    cout << "count 6: " << bt.count(6) << endl;
    cout << "3-th value: " << bt[3] << endl;
    cout << "lower bound 0: " << bt.lower_bound(0) << endl;
    cout << "upper bound 0: " << bt.upper_bound(0) << endl;


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

