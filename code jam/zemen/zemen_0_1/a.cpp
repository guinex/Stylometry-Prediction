#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
#define forn(i,n) for (int i = 0; i < int(n); ++i)
typedef long long ll;
typedef long long i64;
typedef long double ld;
const int inf = int(1e9) + int(1e5);
const ll infl = ll(2e18) + ll(1e10);

int test = 1;
void solve() {
    string s;
    int k;
    cin >> s >> k;
    cout << "Case #" << test++ << ": ";
    int res = 0;
    forn (i, sz(s)) {
        if (s[i] == '+')
            continue;
        if (i + k > sz(s)) {
            cout << "IMPOSSIBLE\n";
            return;
        }
        ++res;
        forn (j, k)
            s[i + j] ^= '+' ^ '-';
    }
    cout << res << '\n';
}

int main() {
    #ifdef LOCAL
    assert(freopen("a.in", "r", stdin));
    #else
    #endif
    int tn;
    cin >> tn;
    forn (i, tn)
        solve();
}
