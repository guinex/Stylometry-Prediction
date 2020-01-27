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

const int B = 110;
int f[B][B];
int d[B][B][B];

void uax(int &a, int b) {
    a = max(a, b);
}

void pre() {
    forn (i, B)
        forn (j, B) {
            if (i || j)
                f[i][j] = 1;
            if (i && j)
                f[i][j] = max(f[i][j], f[i-1][j-1] + 1);
            if (i > 2)
                f[i][j] = max(f[i][j], f[i-3][j] + 1);
            if (j > 2)
                f[i][j] = max(f[i][j], f[i][j-3] + 1);
        }
    forn (i, B)
        forn (j, B)
            forn (k, B) {
                if (i || j || k)
                    d[i][j][k] = 1;
                if (i && k)
                    uax(d[i][j][k], d[i-1][j][k-1] + 1);
                if (j > 1)
                    uax(d[i][j][k], d[i][j-2][k] + 1);
                if (i > 3)
                    uax(d[i][j][k], d[i-4][j][k] + 1);
                if (k > 3)
                    uax(d[i][j][k], d[i][j][k-4] + 1);
                if (i > 1 && j)
                    uax(d[i][j][k], d[i-2][j-1][k] + 1);
                if (k > 1 && j)
                    uax(d[i][j][k], d[i][j-1][k-2] + 1);
            }
}

int cnt[5];

int p2() {
    int res = cnt[0];
    res += (cnt[1] + 1) / 2;
    return res;
}

int p3() {
    int a = cnt[1], b = cnt[2];
    int res = f[a][b];
    res += cnt[0];
    return res;
}

int p4() {
    int a = cnt[1];
    int b = cnt[2];
    int c = cnt[3];
    int res = d[a][b][c];
    return res + cnt[0];
}

int test = 1;
void solve() {
    int n, p;
    cin >> n >> p;
    forn (i, p)
        cnt[i] = 0;
    forn (i, n) {
        int x;
        cin >> x;
        cnt[x % p]++;
    }
    cout << "Case #" << test++ << ": ";
    if (p == 2)
        cout << p2() << '\n';
    else if (p == 3)
        cout << p3() << '\n';
    else if (p == 4)
        cout << p4() << '\n';
    else
        assert(false);
}

int main() {
    #ifdef LOCAL
    assert(freopen("a.in", "r", stdin));
    #else
    #endif
    pre();
    int tn;
    cin >> tn;
    forn (i, tn)
        solve();
}
