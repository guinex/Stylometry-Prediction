#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
#define forn(i,n) for (int i = 0; i < int(n); ++i)
typedef long long ll;
typedef long long i64;
typedef long double ld;
const int inf = int(1e9) + int(1e5);
const ll infl = ll(2e18) + ll(1e10);

const int maxn = 205;
int n;
char a[maxn][maxn];
char b[maxn][maxn];

bool bx[maxn];
bool by[maxn];
bool b1[maxn];
bool b2[maxn];

bool ok(int d1, int d2, int &x, int &y) {
    x = d1 + d2 - n;
    if (x % 2)
        return false;
    x /= 2;
    if (x < 0 || x >= n)
        return false;
    y = d1 - d2 + n;
    if (y % 2)
        return false;
    y /= 2;
    if (y < 0 || y >= n)
        return false;
    return true;
}

int test = 1;
void solve() {
    int m;
    cin >> n >> m;
    forn (i, n) {
        forn (j, n)
            b[i][j] = a[i][j] = '.';
        b[i][n] = a[i][n] = 0;
        bx[i] = by[i] = false;
    }
    forn (i, 2 * n)
        b1[i] = b2[i] = false;
    vector<int> diag;
    for (int i = 1; i < n; ++i) {
        diag.push_back(i);
        diag.push_back(2 * n - i);
    }
    diag.push_back(n);

    forn (i, m) {
        char type;
        int x, y;
        cin >> type >> x >> y;
        --x, --y;
        b[x][y] = a[x][y] = type;
        if (type != 'x') {
            b1[x + y] = true;
            b2[x - y + n] = true;
        }
        if (type != '+') {
            bx[x] = true;
            by[y] = true;
        }
    }

    forn (i, n) {
        if (bx[i])
            continue;
        forn (j, n) {
            if (by[j])
                continue;
            bx[i] = by[j] = true;
            if (b[i][j] == '.')
                b[i][j] = 'x';
            else if (b[i][j] == '+')
                b[i][j] = 'o';
            else
                assert(false);
            break;
        }
    }

    forn (i, 2 * n - 1) {
        if (b1[i])
            continue;
        for (int j: diag) {
            int x, y;
            if (!ok(i, j, x, y) || b2[j])
                continue;
            b1[i] = b2[j] = true;
            if (b[x][y] == '.')
                b[x][y] = '+';
            else if (b[x][y] == 'x')
                b[x][y] = 'o';
            else
                assert(false);
            break;
        }
    }

    int sc = 0;
    forn (i, n)
        forn (j, n)
            if (b[i][j] == 'o')
                sc += 2;
            else if (b[i][j] != '.')
                sc += 1;
    vector<char> op;
    vector<int> ox;
    vector<int> oy;
    forn (i, n)
        forn (j, n)
            if (a[i][j] != b[i][j]) {
                op.push_back(b[i][j]);
                ox.push_back(i);
                oy.push_back(j);
            }
    cout << "Case #" << test++ << ": " << sc << ' ' << sz(op) << '\n';
    //forn (i, n)
        //cerr << b[i] << '\n';
    forn (i, sz(op)) {
        cout << op[i] << ' ' << ox[i] + 1 << ' ' << oy[i] + 1 << '\n';
    }
}

int main() {
    #ifdef LOCAL
    assert(freopen("d.in", "r", stdin));
    #else
    #endif
    int tn;
    cin >> tn;
    forn (i, tn)
        solve();
}
