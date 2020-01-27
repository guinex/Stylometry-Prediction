#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vi seen;
vi seenn;
vi activeedges;
vi co;
vi down;
vi depth;
vector<vector<pii>> ed;

void dfs(int at, int par, int dep) {
	if (par != -1) {
		seen[par] = 1;
		down[par] = at;
		activeedges.push_back(par);
	}

	if (seenn[at]) {
		assert(depth[at] != -1);
		int k = dep - depth[at];
		assert(k <= sz(activeedges));
		rep(i,0,k) {
			int ed = activeedges[sz(activeedges)-1 - i];
			co[ed]++;
		}
		activeedges.pop_back();
		return;
	}

	seenn[at] = 1;
	depth[at] = dep;

	trav(pa, ed[at]) if (!seen[pa.second]) {
		dfs(pa.first, pa.second, dep+1);
	}
	if (par != -1) {
		activeedges.pop_back();
	}
	depth[at] = -1;
}

/*
vi num, st;
int Time;
template<class F>
int dfs(int at, int par, F f) {
	int me = num[at] = ++Time, e, y, top = me;
	trav(pa, ed[at]) if (pa.second != par) {
		tie(y, e) = pa;
		if (num[y]) {
			top = min(top, num[y]);
			if (num[y] < me)
				st.push_back(e);
		} else {
			int si = sz(st);
			int up = dfs(y, e, f);
			top = min(top, up);
			if (up == me) {
				st.push_back(e);
				f(vi(st.begin() + si, st.end()));
				st.resize(si);
			}
			else if (up < me)
				st.push_back(e);
			else throw false;
		}
	}
	return top;
}

template<class F>
void bicomps(F f) {
	num.assign(sz(ed), 0);
	rep(i,0,sz(ed)) if (!num[i]) dfs(i, -1, f);
}

void solve() {
	int N, E;
	cin >> N >> E;
	ed.clear();
	ed.resize(N);
	vector<pii> eds;
	rep(i,0,E) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		ed[a].emplace_back(b, i);
		ed[b].emplace_back(a, i);
		eds.emplace_back(a, b);
	}

	try {
		bicomps([&](const vi& eds) {
			// TODO
		});
		cout << "?" << endl;
	} catch(bool) {
		cout << "IMPOSSIBLE" << endl;
	}
}
*/

void solve() {
	int N, E;
	cin >> N >> E;
	ed.clear();
	ed.resize(N);
	seen.assign(E, 0);
	seenn.assign(N, 0);
	depth.assign(N, -1);
	assert(activeedges.empty());
	co.assign(E, 0);
	down.assign(E, -1);
	vector<pii> eds;
	rep(i,0,E) {
		int a, b;
		cin >> a >> b;
		--a, --b;
		ed[a].emplace_back(b, i);
		ed[b].emplace_back(a, i);
		eds.emplace_back(a, b);
	}

	rep(i,0,N) {
		if (!seenn[i]) {
			dfs(i, -1, 0);
		}
	}

	bool fail = 0;
	rep(i,0,E) if (co[i] == 0) fail = 1;
	if (fail) {
		cout << "IMPOSSIBLE" << endl;
	} else {
		rep(i,0,E) {
			int c = co[i];
			if (down[i] != eds[i].second) c *= -1;
			cout << c << ' ';
		}
		cout << endl;
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
