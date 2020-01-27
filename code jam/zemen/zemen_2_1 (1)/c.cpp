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

const int N = 100;
const int maxn = N * N;
int n, m;
string s[maxn];

namespace ts {
    int n; //number of variables
    bool used[maxn];
    vector<int> g[maxn];
    vector<int> gr[maxn];
    int comp[maxn];
    int res[maxn];

    void addEdge(int u, int v) { //u or v
        if (u == -1)
            u = v;
        if (v == -1)
            v = u;
        //cerr << "edge " << u << ' ' << v << '\n';
        g[u ^ 1].push_back(v);
        g[v ^ 1].push_back(u);
        gr[u].push_back(v ^ 1);
        gr[v].push_back(u ^ 1);
    }

    vector<int> ord;
    void dfs1(int u) {
        used[u] = true;
        for (int v: g[u]) {
            if (used[v])
                continue;
            dfs1(v);
        }
        ord.push_back(u);
    }

    int COL = 0;
    void dfs2(int u) {
        used[u] = true;
        comp[u] = COL;
        for (int v: gr[u]) {
            if (used[v])
                continue;
            dfs2(v);
        }
    }

    bool run() {
        fill(res, res + 2 * n, -1);
        fill(used, used + 2 * n, false);
        forn (i, 2 * n)
            if (!used[i])
                dfs1(i);
        reverse(ord.begin(), ord.end());
        assert((int) ord.size() == (2 * n));
        fill(used, used + 2 * n, false);
        for (int u: ord) if (!used[u]) {
            dfs2(u);
            ++COL;
        }
        forn (i, n) {
            if (comp[i * 2] == comp[i * 2 + 1])
                return false;
            if (comp[i * 2] < comp[i * 2 + 1])
                res[i] = true;
            else
                res[i] = false;
        }
        return true;
    }

    void clear() {
        ord.clear();
        forn (i, 2 * n) {
            g[i].clear();
            gr[i].clear();
            comp[i] = -1;
        }
    }
};

using ts::addEdge;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
int to[N][N][4];
int go(int x, int y, int dir) {
    int &res = to[x][y][dir];
    if (res != -2)
        return res;
    int tx = x + dx[dir];
    int ty = y + dy[dir];
    if (tx < 0 || tx >= n || ty < 0 || ty >= m || s[tx][ty] == '#')
        return res = -1;
    if (s[tx][ty] == '|') {
        res = (tx * m + ty) * 2;
        if (dir == 1 || dir == 3)
            res ^= 1;
        return res;
    }
    if (s[tx][ty] == '-') {
        res = (tx * m + ty) * 2;
        if (dir == 0 || dir == 2)
            res ^= 1;
        return res;
    }
    int ndir = dir;
    if (s[tx][ty] == '/') {
        const int nd[] = {3, 2, 1, 0};
        ndir = nd[dir];
    } else if (s[tx][ty] == '\\') {
        const int nd[] = {1, 0, 3, 2};
        ndir = nd[dir];
    }
    return res = go(tx, ty, ndir);
}

int test = 1;
void solve() {
    cin >> n >> m;
    forn (i, n)
        cin >> s[i];
    forn (i, n)
        forn (j, m)
            forn (d, 4)
                to[i][j][d] = -2;
    ts::n = n * m;
    ts::clear();
    bool FAIL = false;
    forn (i, n)
        forn (j, m) {
            if (s[i][j] == '.') {
                int A = -1, B = -1;
                int u = go(i, j, 0);
                int v = go(i, j, 2);
                if (u != -1)
                    A = u;
                else
                    A = v;
                u = go(i, j, 1);
                v = go(i, j, 3);
                if (u != -1)
                    B = u;
                else
                    B = v;
                if (A != -1 || B != -1)
                    addEdge(A, B);
                else
                    FAIL = true;
            }
            if (s[i][j] == '-' || s[i][j] == '|') {
                int u = go(i, j, 1);
                int v = go(i, j, 3);
                int var = 2 * (i * m + j);
                if (s[i][j] == '|')
                    var ^= 1;
                if (u != -1 || v != -1)
                    addEdge(var ^ 1, var ^ 1);

                u = go(i, j, 0);
                v = go(i, j, 2);
                var ^= 1;
                if (u != -1 || v != -1)
                    addEdge(var ^ 1, var ^ 1);
            }
        }
    if (!ts::run())
        FAIL = true;
    forn (i, n)
        forn (j, m) {
            if (s[i][j] != '|' && s[i][j] != '-')
                continue;
            int xx = '|' ^ '-';
            if (ts::res[i * m + j] == 1)
                s[i][j] ^= xx;
        }
    cout << "Case #" << test++ << ": ";
    if (FAIL)
        cout << "IMPOSSIBLE\n";
    else {
        cout << "POSSIBLE\n";
        forn (i, n)
            cout << s[i] << '\n';
    }
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
