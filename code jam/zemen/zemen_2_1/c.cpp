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
    map<ll, ll> m;

    ll n, k;
    cin >> n >> k;
    m[n] = 1;
    while (k) {
        auto it = prev(m.end());
        ll len = it->first;
        assert(len > 0);
        if (it->second >= k) {
            cout << "Case #" << test++ << ": " << len / 2 << ' ' << (len - 1) / 2 << '\n';
            return;
        }
        k -= it->second;
        m[len / 2] += it->second;
        m[(len - 1) / 2] += it->second;
        m.erase(it);
    }
    assert(false);
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
