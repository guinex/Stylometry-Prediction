#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
#define forn(i,n) for (int i = 0; i < int(n); ++i)
#define all(x) (x).begin(), (x).end()
typedef long long ll;
typedef long long i64;
typedef long double ld;
const int inf = int(1e9) + int(1e5);
const ll infl = ll(2e18) + ll(1e10);
typedef pair<int, int> pii;

const int maxn = 2005;

struct Edge {
    int id, to, tm;
};

vector<Edge> from[maxn];
vector<Edge> to[maxn];

int cost(Edge a, Edge b) {
    if (b.tm < a.tm)
        return b.tm + 24 - a.tm;
    return b.tm - a.tm;
}

struct DSU {
    vector<int> col;

    DSU(int n) {
        col.resize(n);
        iota(all(col), 0);
    }

    int get(int u) {
        if (col[u] == u)
            return u;
        return col[u] = get(col[u]);
    }

    void join(int u, int v) {
        u = get(u), v = get(v);
        col[u] = v;
    }
};

int test = 1;
void solve() {
    int n;
    cin >> n;
    forn (i, 2 * n) {
        from[i].clear();
        to[i].clear();
    }
    int res = 0;
    forn (i, 2 * n) {
        int e, l, d;
        cin >> e >> l >> d;
        --e;
        from[i / 2].push_back(Edge{i, e, l});
        res += d;
        to[e].push_back(Edge{i, i / 2, (l + d) % 24});
    }
    DSU dsu(2 * n);
    vector<pair<int, pii>> es;
    forn (i, n) {
        int c1 = cost(to[i][0], from[i][0]) + cost(to[i][1], from[i][1]);
        int c2 = cost(to[i][0], from[i][1]) + cost(to[i][1], from[i][0]);
        if (i == 0) {
            c1 = from[i][1].tm + cost(to[i][0], from[i][0]);
            c1 = min(c1, from[i][0].tm + cost(to[i][1], from[i][1]));
            c2 = from[i][0].tm + cost(to[i][0], from[i][1]);
            c2 = min(c2, from[i][1].tm + cost(to[i][1], from[i][0]));
        }
        if (c1 > c2) {
            swap(from[i][0], from[i][1]);
            swap(c1, c2);
        }
        //cerr << c1 << ' ' << c2 << '\n';
        dsu.join(from[i][0].id, to[i][0].id);
        dsu.join(from[i][1].id, to[i][1].id);
        res += c1;
        es.emplace_back(c2 - c1, pii{from[i][0].id, from[i][1].id});
    }
    sort(all(es));
    for (auto e: es) {
        int w = e.first;
        int u = e.second.first;
        int v = e.second.second;
        if (dsu.get(u) != dsu.get(v)) {
            dsu.join(u, v);
            res += w;
        }
    }
    cout << "Case #" << test++ << ": " << res << '\n';
}

int main() {
    #ifdef LOCAL
    assert(freopen("c.in", "r", stdin));
    #else
    #endif
    int tn;
    cin >> tn;
    forn (i, tn)
        solve();
}
