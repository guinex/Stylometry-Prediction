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

map<int, vector<int>> s[10];
map<int, int> cnt[10];

int apply(int x, int l) {
    string s(l, '0');
    forn (i, l) {
        int d = x % 10;
        x /= 10;
        if (d)
            s[d - 1]++;
    }
    return stoi(s);
}

void go(int i, int l, int sum, int x = 0) {
    if (l == 9 && sum < 0)
        return;
    if (i == l) {
        //cerr << l << ' ' << x << '\n';
        if (sum >= 0)
            s[l][x] = {};
        else
            cnt[l][apply(x, l)]++;
        return;
    }
    for (int cc = 0; cc <= l; ++cc) {
        int nx = x * 10 + cc;
        go(i + 1, l, sum - cc, nx);
    }
}

void pre(int l) {
    go(0, l, l);
    cerr << "size " << l << ' ' << sz(s[l]) << '\n';
    for (auto &p: s[l]) {
        int x = p.first;
        int y = apply(x, l);
        assert(s[l].count(y));
        s[l][y].push_back(x);
    }
}

set<int> used;
int res;

void dfs(int x, int l) {
    used.insert(x);
    res += cnt[l][x] + 1;
    for (auto y: s[l][x]) {
        if (used.count(y))
            continue;
        dfs(y, l);
    }
}

int calc(int x, int l) {
    used.clear();
    res = 0;
    if (!s[l].count(x))
        return 1;
    dfs(x, l);
    return res;
}

int test = 1;
void solve() {
    string num;
    cin >> num;
    int l = sz(num);
    int x = stoi(num);
    int res = calc(x, l);
    cout << "Case #" << test++ << ": " << res << '\n';
}

int main() {
    #ifdef LOCAL
    assert(freopen("a.in", "r", stdin));
    #else
    #endif
    for (int l = 1; l <= 9; ++l)
        pre(l);
    FILE *f = fopen("a.pre", "r");
    int aa, bb;
    while (fscanf(f, "%d%d", &aa, &bb) == 2)
        cnt[9][aa] = bb;
    fclose(f);
    cerr << "cnt9 " << sz(cnt[9]) << '\n';

    int tn;
    cin >> tn;
    forn (i, tn)
        solve();
}
