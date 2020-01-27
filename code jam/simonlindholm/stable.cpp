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
	int N, R, O, Y, G, B, V;
	cin >> N >> R >> O >> Y >> G >> B >> V;

	int counts[8]{};
	counts[1] = R;
	counts[2] = Y;
	counts[4] = B;
	counts[1+2] = O;
	counts[1+4] = V;
	counts[2+4] = G;
	char lut[8] = {'x', 'R', 'Y', 'O', 'B', 'V', 'G', 'y'};
	int nr = 0;
	int ny = 0;
	int nb = 0;
	rep(i,0,8) if (i & 1) nr += counts[i];
	rep(i,0,8) if (i & 2) ny += counts[i];
	rep(i,0,8) if (i & 4) nb += counts[i];

	if (nr*2 > N || ny*2 > N || nb*2 > N) {
		cout << "IMPOSSIBLE" << endl;
		return;
	}

	string res = "";
	int uselast = 0;
	int usefirst = -1;
	int usenext = -1;
	auto canextendtohave = [&](int bit) {
		rep(i,0,8) {
			if ((i & bit) && !(i & uselast) && !(i & usenext) && counts[i])
				return true;
		}
		return false;
	};
	rep(i,0,N) {
		usenext = (i == N-1 ? usefirst : 0);
		int usethis = 0;
		vector<pii> ord = {{nr*2 + !!(usefirst & 1), 0}, {ny*2 + !!(usefirst & 2), 1}, {nb*2 + !!(usefirst & 4), 2}};
		sort(all(ord));
		reverse(all(ord));
		trav(pa, ord) {
			int bit = 1 << pa.second;
			if (uselast & bit) continue;
			if (usenext & bit) continue;
			if ((usethis && counts[usethis | bit]) || (!usethis && canextendtohave(bit))) {
				usethis |= bit;
			}
			if (bitset<32>(usethis).count() == 2) break;
		}
		assert(usethis != 7);
		if (!usethis) {
			// abort();
// cerr << "WARNING!" << endl;
cerr << N << ' ' << R << ' ' << O << ' ' << Y << ' ' << G << ' ' << B << ' ' << V << endl;
			cout << "IMPOSSIBLE" << endl; return;
		}
		// assert(usethis);
		assert(counts[usethis]);
		counts[usethis]--;
		if (usethis & 1) nr--;
		if (usethis & 2) ny--;
		if (usethis & 4) nb--;
		res += lut[usethis];
		if (i == 0) usefirst = usethis;
		uselast = usethis;
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
