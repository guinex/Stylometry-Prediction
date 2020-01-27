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
    ll n;
    cin >> n;
    while (true) {
        string s = to_string(n);
        bool bad = false;
        forn (i, sz(s) - 1) {
            if (s[i + 1] < s[i]) {
                for (int j = i + 1; j < sz(s); ++j)
                    s[j] = '0';
                bad = true;
                n = stoll(s);
                break;
            }
        }
        if (bad) {
            --n;
            continue;
        }
        cout << "Case #" << test++ << ": " << n << '\n';
        break;
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
