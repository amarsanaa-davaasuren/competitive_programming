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
#define maxs(x, y) x = max(x, y)
#define mins(x, y) x = min(x, y)
#define rep(i, n) for (int(i) = 0; (i) < (n); (i)++)
#define repr(i, n) for (int i = (n)-1; i >= 0; i--)
#define FOR(i, i0, n) for (int(i) = (i0); (i) < (n); (i)++)
#define FORR(i, i0, n) for (int(i) = (n)-1; (i) >= (i0); (i)--)
#define SORT(x) sort(x.begin(), x.end())
#define SORTR(x) sort(x.begin(), x.end(), greater<int>())

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
const int mod = 1e9 + 7;
const int NMAX = 1001000;



#ifndef ATCODER_TWOSAT_HPP
#define ATCODER_TWOSAT_HPP 1

#ifndef ATCODER_INTERNAL_SCC_HPP
#define ATCODER_INTERNAL_SCC_HPP 1

#include <algorithm>
#include <utility>
#include <vector>

#ifndef ATCODER_INTERNAL_CSR_HPP
#define ATCODER_INTERNAL_CSR_HPP 1

#include <algorithm>
#include <utility>
#include <vector>

namespace atcoder {
namespace internal {

template <class E> struct csr {
    std::vector<int> start;
    std::vector<E> elist;
    explicit csr(int n, const std::vector<std::pair<int, E>>& edges)
        : start(n + 1), elist(edges.size()) {
        for (auto e : edges) {
            start[e.first + 1]++;
        }
        for (int i = 1; i <= n; i++) {
            start[i] += start[i - 1];
        }
        auto counter = start;
        for (auto e : edges) {
            elist[counter[e.first]++] = e.second;
        }
    }
};

}  // namespace internal

}  // namespace atcoder

#endif  // ATCODER_INTERNAL_CSR_HPP


namespace atcoder {
namespace internal {

// Reference:
// R. Tarjan,
// Depth-First Search and Linear Graph Algorithms
struct scc_graph {
  public:
    explicit scc_graph(int n) : _n(n) {}

    int num_vertices() { return _n; }

    void add_edge(int from, int to) { edges.push_back({from, {to}}); }

    // @return pair of (# of scc, scc id)
    std::pair<int, std::vector<int>> scc_ids() {
        auto g = csr<edge>(_n, edges);
        int now_ord = 0, group_num = 0;
        std::vector<int> visited, low(_n), ord(_n, -1), ids(_n);
        visited.reserve(_n);
        auto dfs = [&](auto self, int v) -> void {
            low[v] = ord[v] = now_ord++;
            visited.push_back(v);
            for (int i = g.start[v]; i < g.start[v + 1]; i++) {
                auto to = g.elist[i].to;
                if (ord[to] == -1) {
                    self(self, to);
                    low[v] = std::min(low[v], low[to]);
                } else {
                    low[v] = std::min(low[v], ord[to]);
                }
            }
            if (low[v] == ord[v]) {
                while (true) {
                    int u = visited.back();
                    visited.pop_back();
                    ord[u] = _n;
                    ids[u] = group_num;
                    if (u == v) break;
                }
                group_num++;
            }
        };
        for (int i = 0; i < _n; i++) {
            if (ord[i] == -1) dfs(dfs, i);
        }
        for (auto& x : ids) {
            x = group_num - 1 - x;
        }
        return {group_num, ids};
    }

    std::vector<std::vector<int>> scc() {
        auto ids = scc_ids();
        int group_num = ids.first;
        std::vector<int> counts(group_num);
        for (auto x : ids.second) counts[x]++;
        std::vector<std::vector<int>> groups(ids.first);
        for (int i = 0; i < group_num; i++) {
            groups[i].reserve(counts[i]);
        }
        for (int i = 0; i < _n; i++) {
            groups[ids.second[i]].push_back(i);
        }
        return groups;
    }

  private:
    int _n;
    struct edge {
        int to;
    };
    std::vector<std::pair<int, edge>> edges;
};

}  // namespace internal

}  // namespace atcoder

#endif  // ATCODER_INTERNAL_SCC_HPP

namespace atcoder {
#include <cassert>
// Reference:
// B. Aspvall, M. Plass, and R. Tarjan,
// A Linear-Time Algorithm for Testing the Truth of Certain Quantified Boolean
// Formulas
struct two_sat {
  public:
    two_sat() : _n(0), scc(0) {}
    explicit two_sat(int n) : _n(n), _answer(n), scc(2 * n) {}

    void add_clause(int i, bool f, int j, bool g) {
        assert(0 <= i && i < _n);
        assert(0 <= j && j < _n);
        scc.add_edge(2 * i + (f ? 0 : 1), 2 * j + (g ? 1 : 0));
        scc.add_edge(2 * j + (g ? 0 : 1), 2 * i + (f ? 1 : 0));
    }
    bool satisfiable() {
        auto id = scc.scc_ids().second;
        for (int i = 0; i < _n; i++) {
            if (id[2 * i] == id[2 * i + 1]) return false;
            _answer[i] = id[2 * i] < id[2 * i + 1];
        }
        return true;
    }
    std::vector<bool> answer() { return _answer; }

  private:
    int _n;
    std::vector<bool> _answer;
    internal::scc_graph scc;
};

}  // namespace atcoder

#endif  // ATCODER_TWOSAT_HPP


using namespace atcoder;

void solve(){
    

    int n, d;
    n = 3; // 3 flags
    d = 2; // at least distance 2
    vector<int> x = {1,2,0}; // flag i can be placed on the coordinate x_i, y_i
    vector<int> y = {4,5,6}; 


    // ts[i] = (1: i-th flag is located on x[i], 0: on y[i])
    two_sat ts(n);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (abs(x[i] - x[j]) < d) {
                // cannot use both of x[i] and x[j]
                // V -> or. 下記だと、iあるいはjのどれかがfalseじゃないと満たさない条件だ
                ts.add_clause(i, false, j, false); // (not i V not j)  i=false & j=false はダメ      => (x_i=f) ∨ (x_j=g) というクローズを足します    
            }
            if (abs(x[i] - y[j]) < d) {
                ts.add_clause(i, false, j, true); // (not i V j)       i=true & j=false はダメ
            }
            if (abs(y[i] - x[j]) < d) { // (i V not j)                 i=false & j=true はダメ
                ts.add_clause(i, true, j, false);
            }
            if (abs(y[i] - y[j]) < d) { // (i V j)                     i=false & j=false はダメ
                ts.add_clause(i, true, j, true);                       
            }
        }
    }
    // 条件を足す割当が存在するかどうかを判定する。割当が存在するならばtrue、そうでないならfalseを返す
    if (!ts.satisfiable()) {
        cout << "No" << endl;
    }

    cout << "Yes" << endl;
    /***
    最後に呼んだ satisfiable の、クローズを満たす割当を返す。satisfiable を呼ぶ前や、satisfiable 
    で割当が存在しなかったときにこの関数を呼ぶと、中身が未定義の長さ nn の vectorを返す。
    ***/
    auto answer = ts.answer();
    for (int i = 0; i < n; i++) {
        if (answer[i]) // 1: x[i]にflagを置く, 0: y[i]にフラグを置く
            cout << x[i] << endl;
        else
            cout << y[i] << endl;
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