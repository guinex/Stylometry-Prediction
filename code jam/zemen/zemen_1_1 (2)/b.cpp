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

int n, c, m;

int test = 1;
void solve() {
    cin >> n >> c >> m;
    vector<int> cnt(c);
    vector<int> pr(n);
    forn (i, m) {
        int p, b;
        cin >> p >> b;
        --p, --b;
        cnt[b]++;
        pr[p]++;
    }
    int res = 0;
    forn (i, c)
        res = max(res, cnt[i]);
    int bal = 0;
    forn (i, n) {
        bal += pr[i];
        res = max(res, (bal + i) / (i + 1));
    }
    int bad = 0;
    forn (i, n) {
        bad += max(0, pr[i] - res);
    }
    cout << "Case #" << test++ << ": " << res << ' ' << bad << '\n';
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
