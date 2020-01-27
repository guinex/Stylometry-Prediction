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
	int N, Q;
	cin >> N >> Q;
	vector<vector<ll>> d(N, vector<ll>(N));
	const ll inf = 1LL << 60;
	vector<ll> cap(N);
	vector<double> spd(N);
	rep(i,0,N) {
		cin >> cap[i] >> spd[i];
	}

	rep(i,0,N) rep(j,0,N) {
		cin >> d[i][j];
		if (d[i][j] == -1) d[i][j] = inf;
	}
	rep(i,0,N) d[i][i] = 0;

	rep(k,0,N) rep(i,0,N) rep(j,0,N)
		d[i][j] = min(d[i][j], d[i][k] + d[k][j]);

	rep(qi,0,Q) {
		int s, t;
		cin >> s >> t;
		--s, --t;
		vector<double> timeto(N, INFINITY);
		vi seen(N);
		timeto[s] = 0;
		rep(iter,0,N) {
			double bestt = INFINITY;
			int bestj = -1;
			rep(j,0,N) if (!seen[j] && timeto[j] < bestt) {
				bestt = timeto[j];
				bestj = j;
			}
			if (bestj == -1) break;
			seen[bestj] = 1;

			rep(i,0,N) if (!seen[i] && d[bestj][i] <= cap[bestj]) {
				double tim = bestt + d[bestj][i] / spd[bestj];
				timeto[i] = min(timeto[i], tim);
			}
		}

		cout << setprecision(10) << fixed << timeto[t] << ' ';
	}
	cout << endl;
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
