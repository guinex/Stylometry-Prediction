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

int n, m;

struct Edge {
    int to, id, inv;
};

const int maxn = 4005;
vector<Edge> g[maxn];
bool used[maxn];
int in[maxn];
int up[maxn];
int timer;
bool FAIL;
int ans[maxn];
int h[maxn];

vector<int> st;
vector<int> sgn;
void dfs(int u, int prev = -1) {
    used[u] = true;
    up[u] = in[u] = timer++;
    for (auto e: g[u]) {
        int v = e.to;
        int id = e.id;
        if (prev == id)
            continue;
        if (used[v]) {
            if (in[v] < in[u]) {
                up[u] = min(up[u], in[v]);
                ans[id] += e.inv;
                for (int j = h[v]; j < sz(st); ++j)
                    ans[st[j]] += sgn[j];
            }
        } else {
            st.push_back(id);
            sgn.push_back(e.inv);
            h[v] = h[u] + 1;
            dfs(v, id);
            st.pop_back();
            sgn.pop_back();

            if (up[v] == in[v])
                FAIL = true;
            up[u] = min(up[u], up[v]);
        }
    }
}

int test = 1;
void solve() {
    cin >> n >> m;
    forn (i, n) {
        g[i].clear();
        used[i] = false;
        h[i] = 0;
    }
    forn (i, m)
        ans[i] = 0;
    //cerr << "nm " << n << ' ' << m << '\n';
    FAIL = false;
    timer = 0;
    forn (i, m) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(Edge{v, i, 1});
        g[v].push_back(Edge{u, i, -1});
    }
    forn (i, n) {
        if (used[i])
            continue;
        dfs(i);
    }
    cout << "Case #" << test++ << ":";
    if (FAIL)
        cout << " IMPOSSIBLE\n";
    else {
        forn (u, n) {
            int sum = 0;
            for (auto e: g[u])
                sum += ans[e.id] * e.inv;
            assert(sum == 0);
        }
        forn (i, m) {
            assert(ans[i] != 0);
            assert(abs(ans[i]) <= n * n);
        }

        forn (i, m)
            cout << " " << ans[i];
        cout << '\n';
    }
}

int main() {
    #ifdef LOCAL
    assert(freopen("b.in", "r", stdin));
    #else
    #endif
    int tn;
    cin >> tn;
    forn (i, tn)
        solve();
}
