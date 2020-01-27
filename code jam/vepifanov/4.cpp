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
int o[10];
map<string, int> num[10];
int f[11];
vs gl[10];
vi rv[10][50000];
int res[10][50000];
int was[10][50000];

int gen (int i, int sum, int n, string s) {
	if (i == n) {
		gl[n].pb (s);
		num[n][s] = o[n]++;
		re 0;
	}
	for (int t = 0; t <= n && sum + t <= n; t++) gen (i + 1, sum + t, n, s + char ('0' + t));
	re 0;
}

string calc (string s) {
	int n = sz (s);
	int now[10];
	memset (now, 0, sizeof (now));
	for (int i = 0; i < n; i++) now[s[i] - '0']++;
	string t = "";
	for (int i = 1; i <= n; i++) t += char (now[i] + '0');
//	sort (all (t));
	re t;
}

int go (int n, int x, int sx) {	
	if (was[n][x]) re 0;
	was[n][x] = 1;
	int cur = 1;
	for (int i = 0; i < sz (rv[n][x]); i++)
		cur += go (n, rv[n][x][i], sx);
	if (rv[n][x].empty ()) {
		int tmp = f[n];
		int tmp2 = n;
		for (int i = 0; i < n; i++) {
			tmp /= f[gl[n][x][i] - '0'];
			tmp2 -= gl[n][x][i] - '0';
		}
		tmp /= f[tmp2];
		cur += tmp;
	}
	re cur;
}

int main () {
	f[0] = 1;
	for (int i = 1; i <= 10; i++) f[i] = f[i - 1] * i;
	for (int i = 1; i <= 9; i++) {
		gen (0, 0, i, "");
		for (int j = 0; j < o[i]; j++) {
			string s = gl[i][j];
			string t = calc (s);
			assert (num[i].count (t));
//			cout << s << " -> " << t << endl;
			rv[i][num[i][t]].pb (num[i][s]);
		}
		for (int j = 0; j < o[i]; j++) {
			memset (was[i], 0, sizeof (was[i]));
			res[i][j] = go (i, j, j);
//			printf ("%d %s = %d\n", i, gl[i][j].c_str (), res[i][j]);
		}
		cerr << i << " " << o[i] << endl;
	}	
	int tt;
	cin >> tt;
	for (int it = 1; it <= tt; it++) {
		string s;
		cin >> s;
//		sort (all (s));
		n = sz (s);
		cout.precision (20);
		cout << "Case #" << it << ": " << res[n][num[n][s]];
		cout << endl;
		fprintf (stderr, "%d / %d = %.2f | %.2f\n", it, tt, (double)clock () / CLOCKS_PER_SEC, ((double)clock () / it * tt) / CLOCKS_PER_SEC);
	}
	return 0;
}