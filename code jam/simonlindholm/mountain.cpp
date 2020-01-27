#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int delta(int a, int b) {
	int r = b - a;
	return r < 0 ? r + 24 : r;
}

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool same_set(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	void join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
	}
};

void solve() {
	int N;
	cin >> N;
	ll res = 0;
	vector<vector<pii>> departures(N);
	vector<vector<pii>> arrivals(N);
	rep(i,0,2*N) {
		int start = i/2, end, leave, dur;
		cin >> end >> leave >> dur;
		--end;
		int arrive = (leave + dur) % 24;
		res += dur;
		arrivals[end].emplace_back(arrive, i);
		departures[start].emplace_back(leave, i);
	}

	vi next(2*N, -10);
	vector<pair<int, pii>> canjointours;
	rep(i,1,N) {
		vector<pii>& dep = departures[i];
		vector<pii>& arr = arrivals[i];
		assert(sz(dep) == 2);
		assert(sz(arr) == 2);
		vi costs(2);
		rep(j,0,2) {
			int cost = 0;
			rep(k,0,2) {
				cost += delta(arr[k].first, dep[k^j].first);
			}
			costs[j] = cost;
		}
		if (costs[0] < costs[1]) {
			next[arr[0].second] = dep[0].second;
			next[arr[1].second] = dep[1].second;
			canjointours.emplace_back(costs[1] - costs[0], pii(arr[0].second, arr[1].second));
			res += costs[0];
		} else {
			next[arr[0].second] = dep[1].second;
			next[arr[1].second] = dep[0].second;
			canjointours.emplace_back(costs[0] - costs[1], pii(arr[0].second, arr[1].second));
			res += costs[1];
		}
	}
	
	// i = 0
	{
		vector<pii>& dep = departures[0];
		vector<pii>& arr = arrivals[0];
		assert(sz(dep) == 2);
		assert(sz(arr) == 2);
		vi costs(2);
		rep(j,0,2) {
			int cost = min(
				delta(arr[0].first, dep[j].first) + delta(0, dep[1^j].first),
				delta(arr[1].first, dep[1^j].first) + delta(0, dep[j].first)
			);
			costs[j] = cost;
		}
		if (costs[0] < costs[1]) {
			next[arr[0].second] = dep[0].second;
			next[arr[1].second] = dep[1].second;
			canjointours.emplace_back(costs[1] - costs[0], pii(arr[0].second, arr[1].second));
			res += costs[0];
		} else {
			next[arr[0].second] = dep[1].second;
			next[arr[1].second] = dep[0].second;
			canjointours.emplace_back(costs[0] - costs[1], pii(arr[0].second, arr[1].second));
			res += costs[1];
		}
	}

	UF uf(2*N);
	rep(i,0,2*N) {
		assert(next[i] >= 0);
		uf.join(i, next[i]);
	}

	sort(all(canjointours));
	trav(pa, canjointours) {
		pii se = pa.second;
		if (uf.find(se.first) != uf.find(se.second)) {
			uf.join(se.first, se.second);
			res += pa.first;
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
