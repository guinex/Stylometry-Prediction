#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef ll Flow;
struct Edge {
	int dest, back;
	Flow f, c;
};
typedef vector<vector<Edge> > graph;

struct PushRelabel {
	graph g;
	vector<Flow> ec;
	vector<Edge*> cur;
	vector<vi> hs; vi H;
	PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n) {}

	void add_edge(int s, int t, Flow cap, Flow rcap=0) {
		if (s == t) return;
		Edge a = {t, sz(g[t]), 0, cap};
		Edge b = {s, sz(g[s]), 0, rcap};
		g[s].push_back(a);
		g[t].push_back(b);
	}

	void add_flow(Edge& e, Flow f) {
		Edge &back = g[e.dest][e.back];
		if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
		e.f += f; e.c -= f; ec[e.dest] += f;
		back.f -= f; back.c += f; ec[back.dest] -= f;
	}
	Flow maxflow(int s, int t) {
		int v = sz(g); H[s] = v; ec[t] = 1;
		vi co(2*v); co[0] = v-1;
		rep(i,0,v) cur[i] = g[i].data();
		trav(e, g[s]) add_flow(e, e.c);

		for (int hi = 0;;) {
			while (hs[hi].empty()) if (!hi--) return -ec[s];
			int u = hs[hi].back(); hs[hi].pop_back();
			while (ec[u] > 0)  // discharge u
				if (cur[u] == g[u].data() + sz(g[u])) {
					H[u] = 1e9;
					trav(e, g[u]) if (e.c && H[u] > H[e.dest]+1)
						H[u] = H[e.dest]+1, cur[u] = &e;
					if (++co[H[u]], !--co[hi] && hi < v)
						rep(i,0,v) if (hi < H[i] && H[i] < v)
							--co[H[i]], H[i] = v + 1;
					hi = H[u];
				} else if (cur[u]->c && H[u] == H[cur[u]->dest]+1)
					add_flow(*cur[u], min(ec[u], cur[u]->c));
				else ++cur[u];
		}
	}
};

void solve() {
	int N, M;
	cin >> N >> M;
	map<pii, char> input, output;
	vi rows(N), cols(N);
	vi diag1(N*2), diag2(N*2);
	map<pii, int> mat;
	int res = 0;
	rep(i,0,M) {
		char type;
		int r, c;
		cin >> type >> r >> c;
		--r, --c;
		input[pii(r, c)] = type;
		int val = 0;
		if (type != '+') val |= 1, rows[r] = 1, cols[c] = 1, res++;
		if (type != 'x') val |= 2, diag1[r+c] = 1, diag2[r-c+N] = 1, res++;
		mat[pii(r, c)] = val;
	}

	int j = 0;
	rep(i,0,N) if (!rows[i]) {
		while (cols[j]) j++;
		mat[pii(i, j)] |= 1;
		j++;
		res++;
	}

	PushRelabel pr(4*N+2);
	rep(i,0,2*N) {
		if (!diag1[i]) pr.add_edge(4*N, i, 1);
		if (!diag2[i]) pr.add_edge(2*N+i, 4*N+1, 1);
	}

	rep(r,0,N) rep(c,0,N) {
		pr.add_edge(r+c, r-c+3*N, 1);
	}

	res += (int)pr.maxflow(4*N, 4*N+1);
	rep(i,0,2*N) {
		trav(e, pr.g[i]) if (e.f - pr.g[e.dest][e.back].f > 0) {
			int j = e.dest - 3*N;
			int r = (i + j) / 2;
			int c = (i - j) / 2;
			mat[pii(r,c)] |= 2;
		}
	}

	trav(pa, mat) {
		char ch;
		if (pa.second == 1) ch = 'x';
		else if (pa.second == 2) ch = '+';
		else if (pa.second == 3) ch = 'o';
		else assert(0);
		output[pa.first] = ch;
	}

	vector<pair<pii, char>> out2;
	trav(pa, output) {
		if (input[pa.first] == pa.second) continue;
		out2.push_back(pa);
	}
	cout << res << ' ' << sz(out2) << endl;
	trav(pa, out2) {
		cout << pa.second << ' ' << pa.first.first+1 << ' ' << pa.first.second+1 << endl;
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
