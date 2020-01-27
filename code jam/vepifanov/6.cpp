#include <bits/stdc++.h>

using namespace std;

#define mp make_pair
#define pb push_back
#define rep(i,n) for(int i = 0; i < (n); i++)
#define re return
#define fi first
#define se second
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define sqrt(x) sqrt(abs(x))
#define y0 y3487465
#define y1 y8687969
#define fill(x,y) memset(x,y,sizeof(x))
#define prev PREV
                         
typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef double D;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<string> vs;
typedef vector<vi> vvi;

template<class T> T abs(T x) { re x > 0 ? x : -x; }
template<class T> T sqr(T x) { re x * x; }
template<class T> T gcd(T a, T b) { re a ? gcd (b % a, a) : b; }

int n;
int m;

int g[50000][6];

int num[1000001];
vi v[1000001];
int was[1000001];
int q[1000001];
int p[1000001];
vi w;
int ct;

int go (int x) {
	if (was[x] == ct) re 0;
	if (x == -1) re 1;
	was[x] = ct;
	for (int i = 0; i < sz (v[x]); i++)
		if (go (p[v[x][i]])) {
			q[x] = v[x][i];
			p[v[x][i]] = x;
			re 1;
		}
	re 0;
}

int main () {
	int tt;
	cin >> tt;
	for (int it = 1; it <= tt; it++) {
		cin >> n;
		w.clear ();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < 6; j++) {
				cin >> g[i][j];
				w.pb (g[i][j]);
			}
		sort (all (w));
		w.resize (unique (all (w)) - w.begin ());
		for (int i = 0; i < sz (w); i++) {
			num[w[i]] = i;
			v[i].clear ();
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < 6; j++)
				v[num[g[i][j]]].pb (i);
		int ans = 0;
		memset (was, 0, sizeof (was));
		ct = 0;
		for (int j = 0; j < n; j++) p[j] = -1;
		for (int i = 0; i < sz (w); i++) q[i] = -1;
		for (int i = 0, j = 0; i < sz (w); i++) {
			while (j < sz (w)) {
				if (w[j] != w[i] + (j - i)) break;
				ct++;
				if (!go (j)) break;
				j++;
			}
			ans = max (ans, j - i);
			p[q[i]] = -1;
		}
		cout << "Case #" << it << ": " << ans;
		cout << endl;
		fprintf (stderr, "%d / %d = %.2f | %.2f\n", it, tt, (double)clock () / CLOCKS_PER_SEC, ((double)clock () / it * tt) / CLOCKS_PER_SEC);
	}
	return 0;
}