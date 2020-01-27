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

int n;
int m;
int k;
vii sol, tur;
int res[1 << 10][1 << 10];
int can[1 << 10][10];
int fire[100][100];
string s[100];
int ct;
int was[100][100];
int d[100][100];
ii q[100*100];


int go (int msol, int mtur, int i) {
	if (res[msol][mtur]) re res[msol][mtur];
	int cur = i;
	for (int a = 0; a < sz (sol); a++)
		if (((msol >> a) & 1) == 0)
			for (int b = 0; b < sz (tur); b++)
				if (((mtur >> b) & 1) == 0 && ((can[mtur][a] >> b) & 1))
					cur = max (cur, go (msol | (1 << a), mtur | (1 << b), i + 1));
	re res[msol][mtur] = cur;
}

int out (int msol, int mtur, int i) {
	for (int a = 0; a < sz (sol); a++)
		if (((msol >> a) & 1) == 0)
			for (int b = 0; b < sz (tur); b++)
				if (((mtur >> b) & 1) == 0 && ((can[mtur][a] >> b) & 1))
					if (go (msol | (1 << a), mtur | (1 << b), i + 1) == res[msol][mtur]) {
//						printf ("%d %d | %d %d -> %d %d\n", a + 1, b + 1, sol[a].fi, sol[a].se, tur[b].fi, tur[b].se);
						printf ("%d %d\n", a + 1, b + 1);
						out (msol | (1 << a), mtur | (1 << b), i + 1);
						re 0;
					}
	re 0;
}

int main () {
	int tt;
	cin >> tt;
	for (int it = 1; it <= tt; it++) {
		cin >> m >> n >> k;
		for (int i = 0; i < n; i++) cin >> s[i];
		sol.clear ();
		tur.clear ();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				if (s[i][j] == 'S')
					sol.pb (mp (i, j));
				else
				if (s[i][j] == 'T')	
					tur.pb (mp (i, j));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				fire[i][j] = 0;
		for (int i = 0; i < sz (tur); i++) {
			fire[tur[i].fi][tur[i].se] |= 1 << i;
			for (int t = 0; t < 4; t++) {
				int ii = tur[i].fi;
				int jj = tur[i].se;
				while (true) {
					ii += int (t == 0) - int (t == 1);
					jj += int (t == 2) - int (t == 3);
					if (ii < 0 || jj < 0 || ii >= n || jj >= m || s[ii][jj] == '#') break;
					fire[ii][jj] |= 1 << i;
				}
			}
		}
/*		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				for (int t = 0; t < 4; t++) {
					must[i][j][t] = 0;
					int ni = i + int (t == 0) - int (t == 1);
					int nj = j + int (t == 2) - int (t == 3);
					if (ni < 0 || nj < 0 || ni >= n || nj >= m || s[ni][nj] == '#') continue;
				}*/
		for (int mask = 0; mask < (1 << sz (tur)); mask++)
			for (int i = 0; i < sz (sol); i++) {
				can[mask][i] = 0;
				int l = 0, r = 1;
				ct++;
				was[sol[i].fi][sol[i].se] = ct;
				d[sol[i].fi][sol[i].se] = 0;
				q[0] = sol[i];
				while (l < r) {
					int ii = q[l].fi;
					int jj = q[l].se;
					l++;
					can[mask][i] |= fire[ii][jj];
//					printf ("%d %d %d | %d %d = %d\n", mask, sol[i].fi, sol[i].se, ii, jj, can[mask][i]);
					if (d[ii][jj] < k)
						for (int t = 0; t < 4; t++) {
							int ni = ii + int (t == 0) - int (t == 1);
							int nj = jj + int (t == 2) - int (t == 3);
							if (ni < 0 || nj < 0 || ni >= n || nj >= m || s[ni][nj] == '#' || was[ni][nj] == ct) continue;
//                            int must = (fire[ii][jj] ^ fire[ni][nj]) & fire[ii][jj];
							int must = fire[ii][jj];
                            if ((must & mask) != must) continue;
                            was[ni][nj] = ct;
                            d[ni][nj] = d[ii][jj] + 1;
                            q[r++] = mp (ni, nj);
						}
				}
			}
		memset (res, 0, sizeof (res));
		go (0, 0, 0);
		cout << "Case #" << it << ": " << res[0][0] << endl;
		out (0, 0, 0);
		fprintf (stderr, "%d / %d = %.2f | %.2f\n", it, tt, (double)clock () / CLOCKS_PER_SEC, ((double)clock () / it * tt) / CLOCKS_PER_SEC);
	}
	return 0;
}