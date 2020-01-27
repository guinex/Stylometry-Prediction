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
	ll N, K;
	cin >> N >> K;
	map<ll, ll> seqs;
	seqs[-N] = 1;
	for (;;) {
		auto pa2 = *seqs.begin();
		auto pa = make_pair(-pa2.first, pa2.second);
		seqs.erase(seqs.begin());
		ll lo = (pa.first-1) / 2;
		ll hi = (pa.first) / 2;
		if (pa.second >= K) {
			cout << hi << ' ' << lo << endl;
			return;
		}
		K -= pa.second;
		seqs[-lo] += pa.second;
		seqs[-hi] += pa.second;
	}
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
