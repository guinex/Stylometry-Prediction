#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
#define forn(i,n) for (int i = 0; i < int(n); ++i)
typedef long long ll;
typedef long long i64;
typedef long double ld;
const int inf = int(1e9) + int(1e5);
const ll infl = ll(2e18) + ll(1e10);

const int maxn = 10010;
ll r[maxn];
vector<ll> s[maxn];

int test = 1;
void solve() {
    int n, p;
    cin >> n >> p;
    forn (i, n)
        s[i].clear();
    forn (i, n)
        cin >> r[i];
    forn (i, n) {
        forn (j, p) {
            ll x;
            cin >> x;
            s[i].push_back(x);
        }
        sort(s[i].begin(), s[i].end());
        reverse(s[i].begin(), s[i].end());
    }
    int res = 0;
    for (ll k = 1; k <= int(1e6); ++k) {
        bool ok = true;
        bool shit = false;
        forn (i, n) {
            if (s[i].empty()) {
                shit = true;
                break;
            }
            ll x = s[i].back();
            ll y = r[i] * k;
            if (10 * x < y * 9) {
                s[i].pop_back();
                --i;
                continue;
            }
            if (10 * x > y * 11) {
                ok = false;
                break;
            }
        }
        if (!ok)
            continue;
        if (shit)
            break;
        forn (i, n) {
            s[i].pop_back();
        }
        ++res;
        --k;
    }
    cout << "Case #" << test++ << ": " << res << '\n';
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
