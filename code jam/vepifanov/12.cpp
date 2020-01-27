#include <cstdio>
#include <numeric>
#include <iostream>
#include <vector>
#include <set>
#include <cstring>
#include <string>
#include <map>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <bitset>
#include <queue>
#include <sstream>
#include <deque>

using namespace std;

#define mp make_pair
#define pb push_back
#define rep(i,n) for(int i = 0; i < (n); i++)
#define re return
#define fi first
#define se second
#define sz(x) ((int) (x).size())
#define all(x) (x).begin(), (x).end()
#define sqr(x) ((x) * (x))
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

const string sym = "+xo";

int n;
int m;

int d1[210];
int d2[210];
char w[101][101];
int g[100][100];

int o;
int e;
int was[410];
vii v[410];
int ec[100000];
int u[100][100];

int addedge (int a, int b, int c) {
//	printf ("%d %d %d\n", a, b, c);
	v[a].pb (mp (b, e));
	ec[e] = c;
	e++;
	v[b].pb (mp (a, e));
	ec[e] = 0;
	e++;
	re e - 2;
}

int go (int x, int y) {
	if (x == y) re 1;
	if (was[x]) re 0;
	was[x] = 1;
	for (int i = 0; i < sz (v[x]); i++)
		if (ec[v[x][i].se] && go (v[x][i].fi, y)) {
			ec[v[x][i].se]--;
			ec[v[x][i].se ^ 1]++;
			re 1;
		}
	re 0;
}

int calc () {
	int cur = 0;
	while (true) {
		memset (was, 0, sizeof (was));
		if (!go (o - 2, o - 1)) break;
		cur++;
	}
	re cur;
}

int main () {
	int tt;
	cin >> tt;
	for (int it = 1; it <= tt; it++) {
		cin >> n >> m;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				w[i][j] = '.';
				g[i][j] = 0;
			}	
		int ans = 0;
		for (int i = 0; i < m; i++) {
			string s;
			int a, b;
			cin >> s >> a >> b; a--; b--;
			w[a][b] = s[0];
			g[a][b] = int (s[0] == '+') + 2 * int (s[0] == 'x');
			ans += 1 + int (s[0] == 'o');
		}
		{
			o = 2 * n + 2;
			e = 0;
			for (int i = 0; i < o; i++) v[i].clear ();
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if (w[i][j] == '.' || w[i][j] == '+')
						u[i][j] = addedge (i, j + n, 1);
			for (int i = 0; i < n; i++) {
				int ok = 1;
				for (int j = 0; j < n; j++)
					if (w[i][j] == 'x' || w[i][j] == 'o')
						ok = 0;
				if (ok) addedge (o - 2, i, 1);
			}
			for (int i = 0; i < n; i++) {
				int ok = 1;
				for (int j = 0; j < n; j++)
					if (w[j][i] == 'x' || w[j][i] == 'o')
						ok = 0;
				if (ok) addedge (n + i, o - 1, 1);
			}
			ans += calc ();
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if ((w[i][j] == '.' || w[i][j] == '+') && ec[u[i][j]] == 0)
						g[i][j] |= 2;
		}
//		printf ("\n");
		{
			o = 2 * (2 * n - 1) + 2;
			e = 0;
			for (int i = 0; i < o; i++) v[i].clear ();
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if (w[i][j] == '.' || w[i][j] == 'x')
						u[i][j] = addedge (i + j, 2 * n - 1 + i - j + n - 1, 1);
			for (int i = 0; i < 2 * n - 1; i++) d1[i] = d2[i] = 0;
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if (w[i][j] == '+' || w[i][j] == 'o')
						d1[i + j] = d2[i - j + n - 1] = 1;
			for (int i = 0; i < 2 * n - 1; i++) {
				if (!d1[i]) addedge (o - 2, i, 1);
				if (!d2[i]) addedge (i + 2 * n - 1, o - 1, 1);
			}
			ans += calc ();
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if ((w[i][j] == '.' || w[i][j] == 'x') && ec[u[i][j]] == 0)
						g[i][j] |= 1;
		}
		vector<pair<char, ii> > v;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
//				printf ("%d %d = %c %d\n", i, j, w[i][j], g[i][j]);
				if ((w[i][j] == '.' && g[i][j]) || (w[i][j] != '.' && g[i][j] == 3))
					v.pb (mp (sym[g[i][j] - 1], mp (i + 1, j + 1)));
			}
		cout << "Case #" << it << ": " << ans << " " << sz (v) << endl;
		for (int i = 0; i < sz (v); i++) cout << v[i].fi << " " << v[i].se.fi << " " << v[i].se.se << endl;
		fprintf (stderr, "%d / %d = %.2f | %.2f\n", it, tt, (double)clock () / CLOCKS_PER_SEC, ((double)clock () / it * tt) / CLOCKS_PER_SEC);
	}
	return 0;
}