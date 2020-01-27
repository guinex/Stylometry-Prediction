#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

void solve() {
	string s;
	int k;
	cin >> s >> k;
	vi flips(sz(s)+1);
	bool curflip = false;
	int res = 0;
	rep(i,0,sz(s)) {
		curflip ^= flips[i];
		if ((s[i] == '-') ^ curflip) {
			res++;
			curflip ^= 1;
			if (i + k > sz(s)) {
				cout << "IMPOSSIBLE" << endl;
				return;
			}
			flips[i+k] ^= 1;
		}
	}
	cout << res << endl;
}

int main() {
	cin.sync_with_stdio(false);
	cin.exceptions(cin.failbit | cin.eofbit | cin.badbit);
	cin.tie(0);
	int T;
	cin >> T;
	rep(i,0,T) {
		cout << "Case #" << i+1 << ": ";
		solve();
	}
}
