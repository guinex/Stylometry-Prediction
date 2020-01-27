#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
#define forn(i,n) for (int i = 0; i < int(n); ++i)
typedef long long ll;
typedef long long i64;
typedef long double ld;
const int inf = int(1e9) + int(1e5);
const ll infl = ll(2e18) + ll(1e10);

int tn = 1;
void solve() {
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    forn (i, n)
        cin >> a[i];
    int fs = n;
    forn (i, n) {
        int p = 0;
        while (p < m && a[i][p] == '?')
            ++p;
        if (p == m) {
            if (i)
                a[i] = a[i - 1];
            continue;
        }
        fs = min(fs, i);
        char last = a[i][p];
        forn (j, m) {
            if (a[i][j] == '?')
                a[i][j] = last;
            else
                last = a[i][j];
        }
    }
    forn (i, fs)
        a[i] = a[fs];
    cout << "Case #" << tn++ << ":\n";
    forn (i, n)
        cout << a[i] << '\n';
}

int main() {
    #ifdef LOCAL
    assert(freopen("a.in", "r", stdin));
    #else
    #endif
    int n;
    cin >> n;
    forn (i, n)
        solve();
}
