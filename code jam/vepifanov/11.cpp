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
#include <cassert>

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

int n;
int m;
vector<pair<ii, ii> > v[1000];
vector<pair<ii, ii> > rv[1000];
int col[2000];
int jump[2000];
int sw[1000];

int calc (pair<ii, ii> a, pair<ii, ii> b) {
	re (b.se.fi - (a.se.fi + a.se.se) % 24 + 24) % 24;
}

int go (int x, int xe, int r) {
	if (col[v[x][xe].fi.se]) re 0;
//	printf ("%d -> %d = %d | %d\n", x + 1, v[x][xe].fi.fi + 1, v[x][xe].fi.se + 1, r);
	col[v[x][xe].fi.se] = r;
	int nxe = jump[v[x][xe].fi.se];
	go (v[x][xe].fi.fi, nxe, r);
	re 0;
}

int main () {
	int tt;
	cin >> tt;
	for (int it = 1; it <= tt; it++) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			v[i].clear ();
			rv[i].clear ();
		}
		int ans = 0;
		for (int i = 0; i < n; i++) {
			int a, b, c;
			cin >> a >> b >> c; a--;
			v[i].pb (mp (mp (a, 2 * i), mp (b, c)));
			rv[a].pb (mp (mp (i, 2 * i), mp (b, c)));
			ans += c;
			cin >> a >> b >> c; a--;
			v[i].pb (mp (mp (a, 2 * i + 1), mp (b, c)));
			rv[a].pb (mp (mp (i, 2 * i + 1), mp (b, c)));
			ans += c;
		}
		int t1 = min (calc (rv[0][0], v[0][0]) + v[0][1].se.fi, calc (rv[0][1], v[0][1]) + v[0][0].se.fi);
		int t2 = min (calc (rv[0][0], v[0][1]) + v[0][0].se.fi, calc (rv[0][1], v[0][0]) + v[0][1].se.fi);
		if (t1 < t2) {
			ans += t1;
			jump[rv[0][0].fi.se] = 0;
			jump[rv[0][1].fi.se] = 1;
			sw[0] = t2 - t1;
		} else {
			ans += t2;
			jump[rv[0][0].fi.se] = 1;
			jump[rv[0][1].fi.se] = 0;
			sw[0] = t1 - t2;
		}
		for (int i = 1; i < n; i++) {
			int t1 = calc (rv[i][0], v[i][0]) + calc (rv[i][1], v[i][1]);
			int t2 = calc (rv[i][0], v[i][1]) + calc (rv[i][1], v[i][0]);
			if (t1 < t2) {
				ans += t1;
				jump[rv[i][0].fi.se] = 0;
				jump[rv[i][1].fi.se] = 1;
				sw[i] = t2 - t1;
			} else {
				ans += t2;
				jump[rv[i][0].fi.se] = 1;
				jump[rv[i][1].fi.se] = 0;
				sw[i] = t1 - t2;
			}
		}
		memset (col, 0, sizeof (col));
		int r = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < 2; j++)
				if (!col[v[i][j].fi.se]) {
					r++;
					go (i, j, r);
				}
		cout.precision (20);
		for (int i = 0; i + 1 < r; i++) {
			ii best (1e9, 0);
			for (int j = 0; j < n; j++)
				if (col[v[j][0].fi.se] != col[v[j][1].fi.se] && sw[j] < best.fi) {
					best.fi = sw[j];
					best.se = j;
				}
			ans += best.fi;
			int a = col[v[best.se][0].fi.se];
			int b = col[v[best.se][1].fi.se];
			for (int j = 0; j < 2 * n; j++)
				if (col[j] == b)
					col[j] = a;
		}
		if (ans > 1e9) ans = -1;
		cout << "Case #" << it << ": " << ans;
		cout << endl;
		fprintf (stderr, "%d / %d = %.2f | %.2f\n", it, tt, (double)clock () / CLOCKS_PER_SEC, ((double)clock () / it * tt) / CLOCKS_PER_SEC);
	}
	return 0;
}