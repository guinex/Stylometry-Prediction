#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < int(to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

ll multinomial(vi& v) {
	ll c = 1, m = v.empty() ? 1 : v[0];
	rep(i,1,sz(v)) rep(j,0,v[i])
		c = c * ++m / (j+1);
	return c;
}

string out;
template<class F>
bool genmulti(vi& counts, F f) {
	bool any = 0;
	rep(i,0,sz(counts)) if (counts[i] > 0) {
		out += (char)('0' + i);
		counts[i]--;
		bool r = genmulti(counts, f);
		counts[i]++;
		out.pop_back();
		any = 1;
		if (!r) return false;
	}

	if (!any) {
		return f(out);
	}

	return true;
}

int L;

bool nopre(string& str) {
	vi counts(L+1);
	int sum = 0;
	rep(i,0,L) counts[i+1] = (str[i] - '0'), sum += (str[i] - '0');
	counts[0] = L - sum;
	assert(sum > 0);
	return counts[0] < 0;
}

void solve() {
	string str;
	cin >> str;
	L = sz(str);
	if (nopre(str)) {
		cout << 1 << endl;
		return;
	}

	vi counts(L+1);
	int sum = 0;
	rep(i,0,L) counts[i+1] = (str[i] - '0'), sum += (str[i] - '0');
	counts[0] = L - sum;
	assert(sum > 0);

	queue<string> q;
	q.push(str);
	ll res = 0;
	set<string> seen;
	while (!q.empty()) {
		str = q.front();
		q.pop();
		if (seen.count(str)) continue;
		seen.insert(str);
		counts.assign(L+1, 0);
		sum = 0;
		rep(i,0,L) counts[i+1] = (str[i] - '0'), sum += (str[i] - '0');
		counts[0] = L - sum;

// cerr << str << " -> ";
// trav(x, counts) cerr << x << ' ';
// cerr << endl;

		assert(sum > 0);
		assert(counts[0] >= 0);
		vi counts2 = counts;
		{
			genmulti(counts2, [&](string& s) {
				if (nopre(s)) {
					res += multinomial(counts);
					// cerr << "add " << multinomial(counts) << endl;
					return false;
				}
				q.push(s);
				// cerr << "push " << s << endl;
				return true;
			});
		}
		res++;
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
